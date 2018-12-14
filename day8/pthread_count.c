#include<stdio.h>                                                                     
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<string.h>
#include<fcntl.h>
#include<signal.h>
#include<pthread.h>

#define MAX 5000
//共享资源
//创建一把互斥锁
pthread_mutex_t mutex;
int number;

void* funcA_num(void* arg)
{
	int i;
    for(i = 0;i < MAX; ++i)
    {	
		//访问全局变量之前加锁
		pthread_mutex_lock(&mutex);
    	int cur = number;
        cur++; 
	    number = cur;
	    printf("Thread_A, id = %lu, number = %d\n", pthread_self(), number);
		//操作完共享资源后解锁
		pthread_mutex_unlock(&mutex);
		usleep(10);         
	}
	return NULL;
}


void* funcB_num(void* arg)
{
	int i;
	for(i = 0;i < MAX; ++i)
	{
		//加锁
		pthread_mutex_lock(&mutex);
		int cur = number;
		cur++;
		number = cur;
		printf("Thread_B, id = %lu, number = %d\n", pthread_self(), number);
		//解锁
		pthread_mutex_unlock(&mutex);
		usleep(10);
	}
	return NULL;
}

int main(int argc, const char* argv[])
{
	//初始化锁
	pthread_mutex_init(&mutex, NULL);

	//创建两个子线程
	pthread_t p1, p2;
	pthread_create(&p1, NULL, funcA_num, NULL);
	pthread_create(&p2, NULL, funcB_num, NULL);

	//阻塞，资源回收
	pthread_join(p1, NULL);
	pthread_join(p2, NULL);
	 
	//释放锁资源
	pthread_mutex_destroy(&mutex);
	return 0;
}
