#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<string.h>
#include<signal.h>
#include<sys/wait.h>

int main(int argc, const char* argv[])
{
	pid_t pid = fork();
	if(pid > 0)
	{
		//父进程, 用wait函数 回收子进程资源
		int status;
		pid_t wpid = wait(&status);
		printf("child died pid = %d\n",wpid);
		if(WIFSIGNALED(status))
		{
			printf("died by signal: %d\n", WTERMSIG(status));
		}
	}
	else if(pid == 0)
	{
		//自己给自己发信号
		//raise(SIGINT);
		while(1)
		{
			abort();
		}
	}
	return 0;
}
