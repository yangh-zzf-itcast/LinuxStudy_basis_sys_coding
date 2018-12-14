#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<string.h>
#include<fcntl.h>

int main(int argc, const char* argv[])
{
	//创建一个管道
	int fd[2];
	int ret = pipe(fd);
	if(ret == -1)
	{
		perror("pipe error");
		exit(1);
	}
	
	//创建完管道后再创建子进程
	pid_t pid = fork();

	printf("pipe[0] = %d, pipe[1] = %d\n", fd[0], fd[1]);
	close(fd[0]);
	close(fd[1]);

	return 0;
}

