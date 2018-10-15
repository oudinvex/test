#include<unistd.h>
#include<stdio.h>


int main()
{
	pid_t pid;
	printf("父进程pid：%u ppid:%u \n",getpid(),getppid());
	pid = fork();
	if(pid==-1)
{
	perror("fork fail");
}
	else if(pid==0)
	{
	//子进程
	while(1)
	{
	printf("子进程pid:%u ppid:%u\n",getpid(),getppid());
	sleep(5);
	}
	}
	else
	{
	//父进程
	printf("父进程pid：%u ppid:%u\n",getpid(),getppid());
	sleep(5);
	}
	return 0;
}
