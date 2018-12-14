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
	return NULL;
}


int main(int argc, const char* argv[]) 
{
	int i = 0; 
	pthread_t pthid;
	//初始化线程属性
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	//利用第二个参数，设置线程分离
		//第四个参数传递的是地址，里面的值一直在变  
		int ret = pthread_create(&pthid, &attr, myfunc, NULL);
		if(ret != 0)
		{
			printf("error number: %d\n", ret);
			//打印错误信息
			printf("%s\n", strerror(ret));
		}
	
	//打印父线程ID
	printf("parent thread id:%lu\n", pthread_self());
	
	
	for(i = 0;i < 5;++i)
	{
		printf("parent i = %d\n", i);
	}
	
	//父线程退出后，子线程会被强行退出
	//父子线程都需要抢cpu时间
	sleep(2);
	//释放线程资源
	pthread_attr_destroy(&attr);
	return 0;
}
