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
	//有血缘关系进程通信，创建匿名内存映射区即可
	//不使用文件，fd用 -1 代替，增加标志位 MAP_ANON
	int len = 4096;
	void *ptr = mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANON, -1, 0);
	if(ptr == MAP_FAILED)
	{
		perror("mmap error");
		exit(1);
	}
	
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
