#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<string.h>
#include<fcntl.h>

int main(int argc, const char* argv[])
{
	if(argc < 2)
	{
		printf("./write_fifo\n");
		exit(1);
	}
	
	//判断fifo文件是否存在, 文件名由命令行传参
	int ret = access(argv[1], F_OK);
	if(ret == -1)
	{
		int r = mkfifo(argv[1], 0664);
		if(r == -1)
		{
			perror("mkfifo error");
			exit(1);
		}
		printf("有名管道文件%s创建成功\n", argv[1]);
	}
	//以只写方式打开管道文件
	int fd = open(argv[1], O_WRONLY);
	if(fd == -1)
	{
		perror("open error");
		exit(1);
	}
	char *p = "hello,world";
	//while(1)
	//{
		sleep(1);
		write(fd, p, strlen(p) + 1);
	//}
	close(fd);
	return 0;
}
