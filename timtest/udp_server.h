#ifndef _CHATROOM_H_
#define _CHATROOM_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include</usr/local/mysql/include/mysql.h>
#include <sys/socket.h>
#include <signal.h>
#include <netinet/in.h>  
#include <arpa/inet.h>  
#include <unistd.h>  
#include <signal.h>  
#include <pthread.h>  
#include <semaphore.h>  
#include <termios.h>  
#include <time.h>  
#include <sys/stat.h>  
#include <fcntl.h>  

/*********************注册登录**********************************/  
#define REG             1         //注册  
#define LOG             2         //登录  
#define FORGET          3         //忘记密码  
#define EXIT            4         //退出  
#define EXISTING_ACC    5         //账号已存在  
#define LOGGED_ACC      6         //账号已登录  
#define ERROR           7         //账号或密码错误  
#define LOG_SUCCESS     8         //登录成功  
#define REG_SUCCESS     9         //注册成功  
#define Exit            10        //下线  
/***************************************************************/  

/******************聊天室功能***********************************/  
#define private_chat    11        //私聊  
#define group_chat      12        //群聊  
#define group_result    13        //群聊接受  
#define file_transfer   14        //文件传输  
#define online          15        //查看在线人数  
#define expression      16        //表情  
#define phrases         17        //常用语  
#define kick            24        //踢人  
/***************************************************************/  


/****************服务器返回结果*********************************/  
#define SEND_SUCCESS        27          //发送成功  
#define SEND_FAILED         28          //操作失败
/***************************************************************/  

#endif
