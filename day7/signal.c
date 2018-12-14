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
}
int main(int argc, const char* argv[]) 
{
	//捕捉ctrl + c
	//注册捕捉函数
	signal(SIGINT, myfunc);

	while(1)
	{
		printf("hello world~!\n");
		sleep(1);
	}
	return 0;
}
