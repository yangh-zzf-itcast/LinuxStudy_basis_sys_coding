#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<string.h>
#include<sys/wait.h>

int main(int argc, const char* argv[])
{
	pid_t pid=fork();

	//父进程
	if(pid > 0)
	{
		printf("parent process, pid = %d, ppid = %d\n", getpid(), getppid());
	 	//回收子进程资源
		int status;
		//wait 函数的使用
		//pid_t wpid = wait(&status);
		//waitpid 函数的使用
		pid_t wpid = waitpid(-1, &status, 0); 
		//判断是否正常退出
		if(WIFEXITED(status))
		{
			printf("exit value: %d\n", WEXITSTATUS(status));
		}
		//是否通过信号杀死退出
		if(WIFSIGNALED(status))
		{
			printf("exit by signal: %d\n", WTERMSIG(status));
		}
		printf("died child pid = %d\n", wpid);
	}
	//子进程
	else if(pid == 0)
	{
	    //加了while进程一直运行
	    while(1)
		{
			sleep(1);
			printf("child process, pid = %d, ppid = %d\n", getpid(), getppid());
	    }
	}

	int i;
	for(i = 0;i < 5;i++)
	{
		printf("i = %d\n", i);
	}

	return 9;
}
