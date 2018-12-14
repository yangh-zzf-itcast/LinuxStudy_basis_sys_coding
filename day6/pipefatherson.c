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
	int i;
	//创建一个管道
	int fd[2];
	int ret = pipe(fd);
	if(ret == -1)
	{
		perror("pipe error");
		exit(1);
	}
	
	//创建完管道后再创建子进程
	for(i = 0;i < 2;++i)
	{
		pid_t pid = fork();
		if(pid == -1)
		{
			perror("fork error");
			exit(1);
		}
	}
	//子进程1
	//ps aux
	if(i == 0)
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
	//子进程2
	//grep
	else if(i == 1)
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
	//父进程用于回收子进程
	else if(i == 2)
	{
		close(fd[0]);
		close(fd[1]);
		pid_t wpid;
		while((wpid == waitpid(-1, NULL,WNOHANG)) != -1)
		{
			if(wpid == 0)
			{
				continue;
			}
			printf("child died pid = %d\n", wpid);
		}
	}


    //printf("pipe[0] = %d, pipe[1] = %d\n", fd[0], fd[1]);
	close(fd[0]);
	close(fd[1]);

	return 0;
}

