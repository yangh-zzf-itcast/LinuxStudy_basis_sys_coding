#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<string.h>
#include<fcntl.h>
#include<sys/wait.h>

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
	if(pid == -1)
	{
		perror("fork error");
		exit(1);
	}
	//父进程
	//ps aux
	if(pid > 0)
	{
		//写管道操作,关闭读管道
		close(fd[0]);
		//文件描述符重定向
		//stdout_fileno -> 管道的写入端
		dup2(fd[1], STDOUT_FILENO);
		//执行ps aux
		execlp("ps", "ps", "aux", NULL);
		perror("execlp");
		exit(1);
	}
	//子进程
	//grep
	else if(pid == 0)
	{
		//读管道操作，关闭写管道
		close(fd[1]);
		//文件描述符重定向
		//stdin_fileno -> 管道的写入端
		dup2(fd[0], STDIN_FILENO);
		//执行grep bash
		execlp("grep", "grep", "--color=auto", "bash",  NULL);
		perror("execlp");
		exit(1);
	}


    //printf("pipe[0] = %d, pipe[1] = %d\n", fd[0], fd[1]);
	close(fd[0]);
	close(fd[1]);

	return 0;
}

