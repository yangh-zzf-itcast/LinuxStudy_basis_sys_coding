#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<string.h>
#include<fcntl.h>
#include<sys/mman.h>

int main(int argc, const char* argv[])
{
	//打开磁盘文件
	int fd = open("temp.txt", O_RDWR | O_CREAT, 0664);
	//对文件做个拓展，万一是新创建的，len=0，内存映射区大小为0，无法操作
	ftruncate(fd, 4096);
	int len = lseek(fd, 0, SEEK_END);

	void *ptr = mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if(ptr == MAP_FAILED)
	{
		perror("mmap error");
		exit(1);
	}
	//写操作
	while(1)
	{
		char *p =(char *)ptr;
		strcpy(p, "hello parent, i am you friend!!\n");
		sleep(2);
	}
	
	int ret = munmap(ptr, len);
	if(ret == -1)
	{
		perror("munmap error");
		exit(1);
	}
	return 0;
}
