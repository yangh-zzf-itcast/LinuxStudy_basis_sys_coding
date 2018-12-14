#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<string.h>
#include<fcntl.h>
#include<signal.h>
#include<pthread.h>

void* myfunc(void* arg) 
{
	printf("child thread id:%lu\n", pthread_self());
	int i;
	for(i = 0;i < 5;++i)
	{
		printf("child i = %d\n", i);
		if(i == 2)
		{
			//exit(1);   //不能使用，会退出整个进程，父线程也退出
			int number = 100;
			pthread_exit(NULL);
			//pthread_exit(NULL);
		}
	}
	return NULL;
}

int main(int argc, const char* argv[]) 
{
	int i = 0; 
	//创建一个子线程
	//线程ID
	//pthread_t pthid;
	//pthread_create(&pthid, NULL, myfunc, NULL);
	
	//循环创建5个子线程
	pthread_t pthid;
	
		//第四个参数传递的是地址，里面的值一直在变  
		int ret = pthread_create(&pthid, NULL, myfunc, NULL);
		if(ret != 0)
		{
			printf("error number: %d\n", ret);
			//打印错误信息
			printf("%s\n", strerror(ret));
		}
	
	//打印父线程ID
	printf("parent thread id:%lu\n", pthread_self());
	
	while(1)
	//for(i = 0;i < 5;++i)
	{
		printf("parent i = %d\n", i);
		i++;
	}
	
	//父线程退出后，子线程会被强行退出
	//退出主线程
	pthread_exit(NULL);

	//父子线程都需要抢cpu时间

	return 0;
}
