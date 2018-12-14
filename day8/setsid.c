#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<string.h>
#include<fcntl.h>
#include<signal.h>

int main(int argc, const char* argv[]) 
{
	//创建一个会话
	//设置子进程--会长
	pid_t pid = fork();
	if(pid > 0)
	{
		exit(1);
#if 0
		kill(getpid(), SIGKILL);
		raise(SIGKILL);
		abort();
#endif
	}
	else if(pid == 0)
	{
		//创建会话，变成会长
		//会长就是一个守护进程
		setsid();
		//让子进程一直活着
		while(1);
	}
	return 0;
}
