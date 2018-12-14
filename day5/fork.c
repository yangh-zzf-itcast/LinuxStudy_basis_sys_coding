#include<stdio.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<stdlib.h>
#include<string.h>

int main(void)
{
	pid_t pid;
	int i;
	//这个循环执行一次
	for(i=0;i<4;i++)
	{
		printf("------- i = %d\n", i);
	}
	pid = fork();
	//父进程
	if(pid > 0)
	{
		printf("parent process , pid = %d\n", getpid());
	}
	//子进程
	else if(pid == 0)
	{
		printf("child process, pid = %d, ppid = %d\n", getpid(), getppid());
	}
	//这个循环执行两次
	for(i=0;i<4;++i)
	{
		printf("i = %d\n", i);
	}
	return 0;
}
