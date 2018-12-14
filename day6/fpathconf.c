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
	
	//测试管道缓存区的大小
	long size = fpathconf(fd[0], _PC_PIPE_BUF);
	printf("size of pipe = %d\n", size);
	printf("pipe[0] = %d, pipe[1] = %d\n", fd[0], fd[1]);
	close(fd[0]);
	close(fd[1]);

	return 0;
}

