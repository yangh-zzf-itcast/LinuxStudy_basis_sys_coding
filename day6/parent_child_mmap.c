#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<string.h>
#include<fcntl.h>
#include<sys/mman.h>
#include<sys/wait.h>

int main(int argc, const char* argv[])
{
	//打开一个文件
	int fd = open("english.txt", O_RDWR);
	int len = lseek(fd, 0, SEEK_END);
	
	//创建内存映射区
	void *ptr = mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if(ptr == MAP_FAILED)
	{
		perror("mmap error");
		exit(1);
	}
	close(fd);
	
	//创建子进程
	//父子进程都通过ptr 访问内存映射区
	pid_t pid = fork();
	if(pid == -1)
	{
		perror("fork error");
		exit(1);
	}
	//父进程
	if(pid > 0)
	{
		//内存中写数据
		strcpy((char *)ptr, "I love ZhangZifan!");
		//回收子进程
		wait(NULL);
	}
	//子进程
	else if(pid == 0)
	{
		//读数据
		printf("%s\n", (char *)ptr);
	}

	int ret = munmap(ptr, len);
	if(ret == -1)
	{
		perror("munmap error");
		exit(1);
	}
	return 0;
}
