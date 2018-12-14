#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<string.h>
#include<fcntl.h>

int main(int argc, const char* argv[])
{
	int fd = open("butonglei.txt", O_RDWR);
	if(fd == -1)
	{
		perror("open error");
		exit(1);
	}

	//文件扩展
	int len = lseek(fd, 1000, SEEK_END);
	printf("len = %d\n", len);

	write(fd, "a", 1);
	close(fd);

	return 0;
}
