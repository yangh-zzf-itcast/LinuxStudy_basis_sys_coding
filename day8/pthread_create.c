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
	int num = *(int *)arg;
	//int num = (int)arg;
	//打印子线程ID
	printf("child thread id:%lu, 我是第%d个线程.\n", pthread_self(), num);
	return NULL;
}

int main(int argc, const char* argv[]) 
{
	int i; 
	//创建一个子线程
	//线程ID
	//pthread_t pthid;
	//pthread_create(&pthid, NULL, myfunc, NULL);
	
	//循环创建5个子线程
	pthread_t pthid[5];
	for(i = 0;i < 5;++i)
	{
		//第四个参数传递的是地址，里面的值一直在变  
		int ret = pthread_create(&pthid[i], NULL, myfunc, (void*)(&i));
		if(ret != 0)
		{
			printf("error number: %d\n", ret);
			//打印错误信息
			printf("%s\n", strerror(ret));
		}
		//传值
		//pthread_create(&pthid[i], NULL, myfunc, (void*)i);
	}
	//打印父线程ID
	printf("parent thread id:%lu\n", pthread_self());
	
	for(i = 0;i < 5;++i)
	{
		printf("i = %d\n", i);
	}
	
	//父线程退出后，子线程会被强行退出
	//父子线程都需要抢cpu时间片
	sleep(2);

	return 0;
}
