#include<stdio.h>
#include<unistd.h>

int main()
{
	printf("staring……\n");
	printf("当前进程id为%u\n",getpid());
	printf("当前程序父进程id为%u\n",getppid());
	sleep(15);
	if(-1==system("ping 66.42.33.44 -c 10" ))
{
	printf("fail!");
}
	printf("end……\n");	
	return 0;
}


