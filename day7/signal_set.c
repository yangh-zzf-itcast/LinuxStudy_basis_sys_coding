#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<string.h>
#include<fcntl.h>
#include<signal.h>

int main(int argc, const char* argv[])
{
	//手动屏蔽某些信号
	sigset_t myset;
	//初始化，清空集合
	sigemptyset(&myset);
	//向里面添加要阻塞的信号
	sigaddset(&myset, SIGINT);  //ctrl + c, 2
	sigaddset(&myset, SIGQUIT); //ctrl + \, 3
	sigaddset(&myset, SIGKILL); 
	
	//将自定义信号集设置给内核阻塞信号集
	sigprocmask(SIG_BLOCK, &myset, NULL);

	//每隔1s 读取一次内存的未决信号集
	while(1)
	{
		sigset_t pendset;
		sigpending(&pendset);
		//判断1-31号信号
		int i;
		for(i = 1; i < 32; ++i)
		{
			//对每个信号依次判断
			if(sigismember(&pendset,i))
			{
				printf("信号%d存在, 为1\n", i);
			}
			else
			{
				printf("信号%d不存在, 为0\n", i);
			}
		}
		printf("\n");
		sleep(1);
	}
	return 0;
}
