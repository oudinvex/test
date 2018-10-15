#include"udp_server.h"
#define PORT 8888


typedef struct info
{
    char username[20];               //用户名
    char account[20];                //账号
    char passwd[20];                 //密码
    char from_name[20];              //发信人
    char to_name[20];                //收信人
    char online_name[20][20];        //在线人名
    int  online_num;                 //在线人数
    int  cmd;                        //提取操作符  
    int  result;                     //返回操作结果 
    char msg[1024];                  //发送、接收消息    
    char e_s;                        //确认发送的表情
    char p_s;                        //确认发送的常用语  
    char file_name[50];              //文件名
    char Ftp[2048];                  //文件传输
}Info;

typedef struct node
{
    struct sockaddr_in client_addr;
    char name[20];
    char account[20];
    struct node *next;
}Node, *LinkList;
struct sockaddr_in client_addr;

Info SendBuf;
Info RecvBuf;
LinkList head = NULL;           // 在线用户
int sockfd;         
int ret;


 //注册
void deal_reg(struct sockaddr_in temp_addr)                                     
{  
    char sql[100] = {0};     
	mysql_query(&mysql,"set names utf8");
    sprintf(sql, "insert into user(username, account, passwd) values('%s','%s','%s')",RecvBuf.username, RecvBuf.account, RecvBuf.passwd);     

    char *errmsg = NULL;
    if(mysql_query(&mysql,sql))  
    {  
        fprintf(stderr,"fail to insert data to table list:error:%s\n",mysql_error(&mysql));
	}
	else
        SendBuf.result = EXISTING_ACC;

        ret = sendto(sockfd, &SendBuf, sizeof(SendBuf), 0, (struct sockaddr *)&temp_addr, sizeof(temp_addr));
        if (ret < 0)
        {
            perror("sendto_server_log");
            exit(1);
        }
        return;  
    }  

    SendBuf.result = REG_SUCCESS;
    printf("注册信息：用户名：%s \t 账号：%s \t 密码：%s\n", RecvBuf.username, RecvBuf.account, RecvBuf.passwd);

    ret = sendto(sockfd, &SendBuf, sizeof(SendBuf), 0, (struct sockaddr *)&temp_addr, sizeof(temp_addr));
    if (ret < 0)
    {
        perror("sendto_server_register");
        exit(1);
    }              
    bzero(&SendBuf, sizeof(SendBuf));
}

 //登入
void deal_log(struct sockaddr_in temp_addr)
{
    char **Result = NULL;
    int nRow; // 行数
    int nColumn; // 列数
    int ret;
    char sql[100] = {0};

    sprintf(sql, "select username, passwd, likes, vip, moto from chatroom where account = '%s' and passwd = '%s'", RecvBuf.account, RecvBuf.passwd);
    ret = sqlite3_get_table(ppdb, sql, &Result, &nRow, &nColumn, NULL);
    if (ret != SQLITE_OK)
    {
        perror("sqlite3_get_table_deal_log");
        exit(1);
    }

    if(1 == nRow)
    {
        LinkList tmp = head->next;
        while(tmp != head)  
        {  
            if(!strcmp(tmp->account,RecvBuf.account))
            {    
                SendBuf.result = LOGGED_ACC;         //已登入

                ret = sendto(sockfd, &SendBuf, sizeof(SendBuf), 0, (struct sockaddr *)&temp_addr, sizeof(temp_addr));
                if (ret < 0)
                {
                    perror("sendto_server_log");
                    exit(1);
                }
                return;  
            }  
            tmp = tmp->next;  
        }

        SendBuf.result = LOG_SUCCESS;               // 登入成功 

        LinkList p =(LinkList)malloc(sizeof(Node));
        if(p == NULL)
        {
            printf("malloc error!\n");
            return;
        }           
        if (ret < 0)
        {
            perror("sendto_group_chat_success");
            exit(1);
        }
    }
    else 
    {
        SendBuf.result = SEND_FAILED;
        ret = sendto(sockfd, &SendBuf, sizeof(SendBuf), 0, (struct sockaddr *)&temp_addr, sizeof(temp_addr));
        if (ret < 0)
        {
            perror("sendto_group_chat_failure");
            exit(1);
        }
    }
}

 //查看在线人数
int deal_online(struct sockaddr_in temp_addr)
{
    int i = 0;
    SendBuf.online_num = 0;
    LinkList tmp = head->next;
    while(tmp != head)
    {
        SendBuf.online_num++;
        strcpy(SendBuf.online_name[i],tmp->name);
        i++;
        tmp = tmp->next;
    }
    SendBuf.result = online;

    ret = sendto(sockfd, &SendBuf, sizeof(SendBuf), 0, (struct sockaddr *)&temp_addr, sizeof(temp_addr));
    if(ret == -1)
    {
        perror("sendto_online");
    }
}

 //发送表情(群发)
int deal_expression(struct sockaddr_in temp_addr)
{
    int flag = 0;
    LinkList tmp = head->next;
    while (tmp != head)
    {
        if (tmp->client_addr.sin_port != temp_addr.sin_port)
        {
            flag = 1;

            SendBuf.result = expression;
            strcpy(SendBuf.from_name, RecvBuf.username);
            SendBuf.e_s = RecvBuf.e_s;
            ret = sendto(sockfd, &SendBuf, sizeof(SendBuf), 0, (struct sockaddr *)&tmp->client_addr, sizeof(tmp->client_addr));
            if (ret < 0)
            {
                perror("sendto_face");
                exit(1);
            }
        }
        tmp = tmp->next;
    }
    if (flag)
    {
        SendBuf.result = SEND_SUCCESS;
        ret = sendto(sockfd, &SendBuf, sizeof(SendBuf), 0, (struct sockaddr *)&temp_addr, sizeof(temp_addr));
        if (ret < 0)
        {
            perror("sendto_face_success");
            exit(1);
        }
    }
    else
    {
        SendBuf.result = SEND_FAILED;
        ret = sendto(sockfd, &SendBuf, sizeof(SendBuf), 0, (struct sockaddr *)&temp_addr, sizeof(temp_addr));
        if (ret < 0)
        {
            perror("sendto_face_failure");
            exit(1);
        }
    }
}

 //发送常用语(私发)
int deal_phrases(struct sockaddr_in temp_addr)
{
    int flag = 0;
    LinkList tmp = head->next;
    while(tmp != head)
    {
        if(strcmp(tmp->name,RecvBuf.to_name) == 0 )
        {
            flag = 1;
            SendBuf.result = phrases;
            SendBuf.p_s = RecvBuf.p_s;
            strcpy(SendBuf.from_name,RecvBuf.username);
            ret = sendto(sockfd, &SendBuf, sizeof(SendBuf), 0, (struct sockaddr *)&tmp->client_addr, sizeof(tmp->client_addr));
            if(ret == -1)
            {
                perror("sendto_useful");
                exit(1);
            }
            break;
        }
        tmp=tmp->next;
    }

    if(flag)
    {
         memset(SendBuf.result,0,sizeof(SendBuf.result));
        SendBuf.result = SEND_SUCCESS;
        ret = sendto(sockfd, &SendBuf, sizeof(SendBuf), 0, (struct sockaddr *)&temp_addr, sizeof(temp_addr));
        if(ret == -1)
        {
            perror("sendto_success");
            exit(1);
        }
         printf("%s send message to %s ...\n",userIn.name,userIn.toname);
    }
    else
    {
        SendBuf.result = SEND_FAILED;
        ret = sendto(sockfd, &SendBuf, sizeof(SendBuf), 0, (struct sockaddr *)&temp_addr, sizeof(temp_addr));
        if(ret == -1)
        {
            perror("sendto_failure");
            exit(1);
        }
         printf("%s send error...\n",userIn.name);
    }
}   

 //文件传输
void deal_ftp(struct sockaddr_in temp_addr)
{
    int flag = 0;
    LinkList tmp = head->next;

    while (tmp != head)
    {
        if (strcmp(tmp->name,RecvBuf.to_name) == 0)
        {
            flag = 1;
            strcpy(SendBuf.from_name,RecvBuf.username);
            strcpy(SendBuf.file_name, RecvBuf.file_name);//拷贝文件名
            strcpy(SendBuf.Ftp, RecvBuf.Ftp);//拷贝文件内容

            SendBuf.result = file_transfer;

            ret = sendto(sockfd, &SendBuf, sizeof(SendBuf), 0, (struct sockaddr *)&tmp->client_addr, sizeof(tmp->client_addr));
            if (ret < 0)
            {
                perror("sendto_sendfile");
                exit(1);
            }
        }
        tmp = tmp->next;
    }

    if (1 == flag)
    {
        SendBuf.result = SEND_SUCCESS;
        ret = sendto(sockfd, &SendBuf, sizeof(SendBuf), 0, (struct sockaddr *)&temp_addr, sizeof(temp_addr));
        if (ret < 0)
        {
            perror("sendto_file_success");
            exit(1);
        }
    }
    else 
    {
        SendBuf.result = SEND_FAILED;
        ret = sendto(sockfd, &SendBuf, sizeof(SendBuf), 0, (struct sockaddr *)&temp_addr, sizeof(temp_addr));
        if (ret < 0)
        {
            perror("sendto_file_failure");
            exit(1);
        }
    }   
}


 //下线
int deal_quit(struct sockaddr_in temp_addr)
{
    LinkList tmp = head;

/*  if(tmp->next->next == head)
 *      {
 *              if(strcmp(tmp->next->name, RecvBuf.username ) == 0)
 *                      {
 *                                  LinkList p = tmp->next;
 *                                              tmp->next = p->next;
 *                                                          free(p);
 *                                                                      printf("%s 下线！\n", RecvBuf.username );
 *                                                                                  return;
 *                                                                                          }
 *                                                                                                  tmp = tmp->next;
 *                                                                                                      }
 *                                                                                                      */  printf("name : %s\n", RecvBuf.username);
    while(tmp->next != head)
    {
        if(strcmp(tmp->next->name, RecvBuf.username ) == 0)
        {
            LinkList q = tmp->next;
            tmp->next = q->next;
            free(q);
            printf("%s 下线！\n", RecvBuf.username );
            break;
        }
        tmp = tmp->next;
    }

    ret = sendto(sockfd, &SendBuf, sizeof(SendBuf), 0, (struct sockaddr *)&temp_addr, sizeof(temp_addr));
    if(ret == -1)
    {
        perror("sendto_quit");
    }

    return 0;
}


int main()
{
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;
    int length;
    int flag;
    char sql[100];
    MSQL mysql;
    mysql_init(&mysql);
    head = (LinkList)malloc(sizeof(Node));
    if (NULL == head)
    {
        printf("Malloc Failure!\n");
        return;
    }
    head->next = head;

    sockfd = socket(PF_INET, SOCK_DGRAM, 0);
    if (-1 == sockfd)
    {
        perror("socket");
        exit(1);
    }

    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = PORT;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    ret = bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (ret < 0)
    {
        perror("bind");
        exit(1);
    }

 if(!mysql_real_connect(&mysql,"127.0.0.1","root","123456","chatdb",0,NULL,0))
        {
                fprintf(stderr, "Failed to connect to database: Error: %s\n",
                                mysql_error(&mysql));
                                return 0;
        }

    while (1)
    {
        bzero(&SendBuf, sizeof(SendBuf));

        length = sizeof(client_addr);
        ret = recvfrom(sockfd, &RecvBuf, sizeof(RecvBuf), 0, (struct sockaddr *)&client_addr, &length);
        if (ret < 0)
        {
            perror("recvfrom");
            exit(1);
        }


        switch (RecvBuf.cmd)  
        {  
            

            case (EXIT):                         //退出
            {
                exit(1);
                break;
            }

            case (private_chat):                 //私聊
            {
                deal_private(client_addr);
                break;
            }

            case(group_chat):                   //群聊
            {
                deal_group(client_addr);
                break;
            }

            case(online):                       //查看在线人数
            {
                deal_online(client_addr);
                break;
            }

            case(expression):                    //群发表情
            {
                deal_expression(client_addr);
                break;
            }

            case(phrases):                       //发送常用语
            {
                deal_phrases(client_addr);
                break;
            }   

            case (file_transfer):                //文件传输
            {
                deal_ftp(client_addr);
                break;
            }

            case(Exit):                         // 下线
            {
                printf("NAME : %s\n", RecvBuf.username);
                deal_quit(client_addr);
                break;
            }
        }           
    } 

    return 0;

}
#include"udp_server.h"
#include"udp_server.h"
#define PORT 8888


typedef struct info
{
    char username[20];               //用户名
    char account[20];                //账号
    char passwd[20];                 //密码
    char from_name[20];              //发信人
    char to_name[20];                //收信人
    char online_name[20][20];        //在线人名
    int  online_num;                 //在线人数
    int  cmd;                        //提取操作符  
    int  result;                     //返回操作结果 
    char msg[1024];                  //发送、接收消息    
    char e_s;                        //确认发送的表情
    char p_s;                        //确认发送的常用语  
    char file_name[50];              //文件名
    char Ftp[2048];                  //文件传输
}Info;

typedef struct node
{
    struct sockaddr_in client_addr;
    char name[20];
    char account[20];
    struct node *next;
}Node, *LinkList;
struct sockaddr_in client_addr;

Info SendBuf;
Info RecvBuf;
LinkList head = NULL;           // 在线用户
int sockfd;         
int ret;



 //私聊
int deal_private(struct sockaddr_in temp_addr)
{
    int flag = 0;
    LinkList tmp = head->next;
    while(tmp != head)
    {
        if(!strcmp(tmp->name,RecvBuf.to_name))
        {
            flag = 1;
            strcpy(SendBuf.msg, RecvBuf.msg);
            strcpy(SendBuf.from_name,RecvBuf.username);

            SendBuf.result = private_chat;

            ret = sendto(sockfd, &SendBuf, sizeof(SendBuf), 0, (struct sockaddr *)&tmp->client_addr, sizeof(tmp->client_addr));
            if(ret == -1)
            {
                perror("sendto_pchat");
                exit(1);
            }
            break;
        }
        tmp=tmp->next;
    }

     if(flag)
    {
        SendBuf.result = SEND_SUCCESS;
        ret = sendto(sockfd, &SendBuf, sizeof(SendBuf), 0, (struct sockaddr *)&temp_addr, sizeof(temp_addr));
        if(ret == -1)
        {
            perror("sendto_success");
            exit(1);
        }       
    }
    else
    {
        SendBuf.result = SEND_FAILED;
        ret = sendto(sockfd, &SendBuf, sizeof(SendBuf), 0, (struct sockaddr *)&temp_addr, sizeof(temp_addr));
        if(ret == -1)
        {
            perror("sendto_failure");
            exit(1);
        }
    }
}   

 //群聊
int deal_group(struct sockaddr_in temp_addr)
{
    int flag = 0;
    LinkList tmp = head->next;

    while (tmp != head)
    {
        if (tmp->client_addr.sin_port != temp_addr.sin_port)
        {
            flag = 1;

            SendBuf.result = group_chat;


            strcpy(SendBuf.from_name, RecvBuf.username);
           printf("%s\n",SendBuf.from_name);
            strcpy(SendBuf.msg, RecvBuf.msg);

            ret = sendto(sockfd, &SendBuf, sizeof(SendBuf), 0, (struct sockaddr *)&tmp->client_addr, sizeof(tmp->client_addr));
            if (ret < 0)
            {
                perror("sendto_group_chat");
                exit(1);
            }
        }
        tmp = tmp->next;
    }
    if (flag)
    {
        SendBuf.result = SEND_SUCCESS;
        ret = sendto(sockfd, &SendBuf, sizeof(SendBuf), 0, (struct sockaddr *)&temp_addr, sizeof(temp_addr));
        if (ret < 0)
