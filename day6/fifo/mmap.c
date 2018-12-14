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
	//打开一个文件
	int fd = open("english.txt", O_RDWR);
	//获取文件大小
	int len = lseek(fd, 0, SEEK_END);
	//创建内存映射区域
	void *ptr = mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if(ptr == MAP_FAILED)
	{
		perror("mmap error");
		exit(1);
	}
	printf("%s\n", (char *)ptr);

	//释放映射区
	munmap(ptr, len);
	close(fd);
	return 0;
}

