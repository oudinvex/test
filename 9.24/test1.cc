#include<iostream>
// 必须的头文件
#include <pthread.h>
#include <stdio.h>
#include<unistd.h>
using namespace std;

// 线程的运行函数
void* say_hello(void* args)
{
	while(1)
{
	sleep(1);
}
	return 0;
}

int main()
{
	// 定义线程的 id 变量，多个变量使用数组
	for(int i = 0; i >-1; ++i)
	{
		pthread_t tids[i];
		//参数依次是：创建的线程id，线程参数，调用的函数，传入的函数参数
		int ret = pthread_create(&tids[i], NULL, say_hello, NULL);
		if (ret != 0)
		{
		cout<<i<<endl;
		perror("");
		cout << "pthread_create error: error_code=" << ret << endl;
		break;
		}
	}
	//等各个线程退出后，进程才结束，否则进程强制结束了，线程可能还没反应过来；
	pthread_exit(NULL);


return 0;
}
