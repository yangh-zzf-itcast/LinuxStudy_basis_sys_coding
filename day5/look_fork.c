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
	int number = 5;
	//循环创建子进程
	for(i = 0;i < number;++i)
	{
		pid = fork();
		//如果是子进程则直接跳出，否则子进程也会生出子进程
		if(pid == 0)
		{
			break;
		}
	}
	
	//如何判断是第几个子进程
	//通过循环因子判断
	//i = 5时，表示该进程是父进程
	switch(i)
	{
		case 0:
			printf("first process, pid = %d\n", getpid());
			break;
		case 1:
			printf("second process, pid = %d\n", getpid());
			break;
		case 2:
		    printf("third process, pid = %d\n", getpid());
			break;
		case 3:
			printf("forth process, pid = %d\n", getpid());
			break;
		case 4:
			printf("fivth process, pid = %d\n", getpid());
			break;
		case 5:
			printf("parent process, pid = %d\n", getpid());
			break;
		default:
			break;
	}

	return 0;
}
