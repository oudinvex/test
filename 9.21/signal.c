#include<stdio.h>
#include<sys/types.h>
#include<signal.h>
#include<unistd.h>
void signal_handler(int signum)
{
printf("something happen\n");
}

int main(int argc,char** argv)
{
	int i;
	signal(SIGINT,signal_handler);
	while(i<10)
{
printf("hello\n");
sleep(1);
i++;
}
	return 0;
}
