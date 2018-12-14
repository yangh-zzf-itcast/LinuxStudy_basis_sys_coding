#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<string.h>
#include<fcntl.h>

int main(int argc,const char* argv[])
{
	//打开一个文件
	int fd = open("butonglei", O_RDWR);
	printf("fd = %d\n", fd);
	if(fd == -1)
	{
		printf("打开文件失败！\n");
		perror("open");
	}

	//打开另一个要写入的文件
	int fd1 = open("temp.txt", O_WRONLY | O_CREAT, 0664);
	printf("fd1 = %d\n", fd1);
    if(fd1 == -1)
    {
		printf("打开文件失败！\n");
		perror("open");
	}

	//读取数据
	char buf[4096];
	int len = read(fd, buf, sizeof(buf));
	while(len > 0)
	{
		//数据写入到文件temp中
		int ret = write(fd1, buf, len);
		printf("该次读取数据量ret = %d\n", ret);

		//如果没有读完继续读取文件数据
		len = read(fd, buf, len);
	}

	close(fd);
	close(fd1);

	return 0;
}
