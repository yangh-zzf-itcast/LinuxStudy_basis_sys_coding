#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<string.h>
#include<fcntl.h>
#include<signal.h>

void myfunc(int no)
{
	printf("catch you signal: %d\n", no);
	sleep(3);
	printf("wake up\n");
}
int main(int argc, const char* argv[]) 
{
	struct sigaction myact;
	//初始化
	myact.sa_flags = 0;
	sigemptyset(&myact.sa_mask);

	//添加临时屏蔽的信号
	sigaddset(&myact.sa_mask, SIGQUIT);

	myact.sa_handler = myfunc;
	//捕捉ctrl + c
	//注册捕捉函数
	sigaction(SIGINT, &myact, NULL);

	while(1)
	{
		printf("hello world~!\n");
		sleep(1);
	}
	return 0;
}
