class server
{
	public:
	bool setserversocket();//设置套嵌字
	bool checktxt();//检测存储文件是否存在，如果不存在则创建
	void work();//服务器运行主函数
	void sendmessage(string message,struct sockaddr_in x);//信息发送函数
	void sendonlinelist();//向客户端发送在线好友列表
	bool testusernameandpassword(string username,string password);
	bool testoverlogin(string username);//测试是否重复登录
	bool testovercreate(string username);//测试是否重复注册
	string getusername(string ip,int port);//根据ip和端口获得用户名
	int getuserindex(string username);//获得当前在线用户列表
	void extractloginuserinfor(string userinfor,string&username,string &password,string &receiverport);//提取登录请求中的用户名密码和显示器端口号
	void extactregisteruserinfor(string &message,string &receivername);//提取注册请求中的用户名和密码
	void extactpersonalmessagereceivername(string &message,string &receivername);//提取私聊信息中的接受者的姓名

 private:
	WSAData wsaData;//用来接收信息的套嵌字
	SOCKET sSocket;
	struct sockaddr_in ser;//服务器地址	
	struct sockaddr_in cli;//客户地址
	int cli_length=sizeof(cli);//客户地址长度
	int recv_buf[BUFFER_LENGTH];//接受数据缓冲区
	vector<user> usertable;//在线用户列表
	string sendmessage,printfmessage;//存储服务器转发，打印用的字符串
	int iSend,iRecv;//存储服务器发送和接受的字符串的长度
};
bool server::setserversocket()
{
	//产生服务器端套接口
	sSocket = socket(AF_INET, SOCK_DGRAM, );
	if (sSocket == INVALID_SOCKET)
	{
		cout << "socket()Failed:" << WSAGetLastError() << endl;
		return false;
	}
	//建立服务器端地址
	ser.sin_family = AF_INET;
	ser.sin_port = htons(8888);               //htons()函数把一个双字节主机字节顺序的数转换为网络字节顺序的数
	ser.sin_addr.s_addr = htonl(INADDR_ANY);          //htonl()函数把一个主机字节顺序的数转换为网络字节顺序的数
	if (bind(sSocket, (LPSOCKADDR)&ser, sizeof(ser)) == SOCKET_ERROR)
	{
		cout << "bind()Failed:" << WSAGetLastError() << endl;
		return false;
	}
	return true;
}
