#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<string.h>

int main(int argc, const char* argv[])
{
	//父进程计数
	int i;
	for(i = 0;i < 8;++i)
	{
		printf("parent i = %d\n", i);
	}
	//创建一个子进程
	pid_t pid = fork();
	//让子进程执行 ls 命令
	if(pid == 0)
	{
		//execl 函数调用方式
		//execl("/bin/ls", "ls", "-l", NULL);
		execl("/root/studyLinux/day5/hello", "hello", NULL);
	}
	
	for(i = 0;i < 3;++i)
	{
		printf("------ i = %d\n", i);
	}

	return 0;
}
