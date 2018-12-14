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
	int num = 2;
	int i, status;
	pid_t pid, wpid;
	for(i = 0;i < num;++i)
	{
		pid = fork();
		if(pid == 0)
		{
			break;
		}
	}

	switch(i)
	{
		case 0:
			execlp("ps", "ps", "aux", NULL);
			perror("execlp ps");
			break;
		case 1:
			execl("/root/studyLinux/day5/hello", "hello", NULL);
			perror("execl error");
			break;
		//主进程回收内存	
		case 2:
			//等于 -1 时表示没有子进程还在运行
			//while((wpid = wait(&status)) != -1 )
			while((wpid = waitpid(-1 ,&status, WNOHANG)) != -1)
			{
				//让非阻塞的子进程跳过后面语句
				if(wpid == 0)
				{
					continue;
				}
				printf("-----child died pid = %d\n", wpid);
				if(WIFEXITED(status))
				{
					printf("return value %d\n", WEXITSTATUS(status));
				}
				else if(WIFSIGNALED(status))
				{
					printf("died by signal : %d\n", WTERMSIG(status));
				}
			}
	}

	return 0;
}
