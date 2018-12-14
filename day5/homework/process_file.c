#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<string.h>
#include<fcntl.h>

//操作终端文件 /dev/tty
int main(int argc, const char* argv[])
{
	int fd = open("temp", O_RDWR | O_CREAT, 0664);
	if(fd == -1)
	{
		perror("open error");
		exit(1);
	}

	pid_t pid = fork();
	if(pid == -1)
	{
		perror("fork error");
		exit(1);
	}
	
	//父进程
	if(pid > 0)
	{
		const char* p = "近期，希望Linux开发人员转移到windows开发";
		write(fd, p, strlen(p) + 1);
		close(fd);   //父进程关闭了文件描述符，但子进程复制了其文件描述符号，还可以访问
	}
	else if(pid == 0)
	{
		//让子进程休眠1s， 保证父进程执行写操作完毕
		sleep(1);
		char buf[1024];
		//让文件指针移动到文件起始位置
		lseek(fd, 0, SEEK_SET);
		int len = read(fd, buf, sizeof(buf));
		printf("buf = %s\n", buf);
		close(fd);
	}

	return 0;
}
