#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<string.h>
#include<fcntl.h>
#include<signal.h>
#include<pthread.h>

int number = 0;

//创建读写锁
pthread_rwlock_t rwlock;
//回调函数操作共享资源
void* write_func(void* arg)
{
	//循环写
	while(1)
	{
		//加写锁
		pthread_rwlock_wrlock(&rwlock);
		number++;
		printf("==> write:%lu, %d\n", pthread_self(), number);
		pthread_rwlock_unlock(&rwlock);
		usleep(500);
	}
	return NULL;
}

void* read_func(void* arg)
{
	while(1)
	{
		//加读锁
		pthread_rwlock_rdlock(&rwlock);
		printf("==> read:%lu, %d\n", pthread_self(), number);
		pthread_rwlock_unlock(&rwlock);
		usleep(500);
	}
	return NULL;
}

int main(int argc, const char* argv[])
{
	//初始化读写锁
	pthread_rwlock_init(&rwlock, NULL);
	pthread_t p[8];
	int i;
	//创建3个写线程
	//创建5个读线程
	for(i = 0;i < 3; ++i)
	{
		pthread_create(&p[i], NULL, write_func, NULL);
	}
	for(i = 3;i < 8; ++i)
	{
		pthread_create(&p[i], NULL, read_func, NULL);
	}

	//主线程回收子线程pcb资源
	for(i = 0;i < 8; ++i)
	{
		pthread_join(p[i], NULL);
	}

	//释放读写锁资源
	pthread_rwlock_destroy(&rwlock);
	return 0;
}
