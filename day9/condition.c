#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<string.h>
#include<fcntl.h>
#include<signal.h>
#include<pthread.h>

//生产者，消费者模型实现
//
//节点结构
typedef struct node
{
	int data;
	struct node* next;
}Node;

//线程同步，互斥锁
pthread_mutex_t mutex;

//阻塞线程，条件变量
pthread_cond_t cond;

//定义一个指针，永远指向链表头部
Node* head = NULL;

//生产者负责生产
void* producer(void* arg)
{
	while(1)
	{
		//创建一个新节点，头插法
		Node* pnew = (Node*)malloc(sizeof(Node));
		//节点初始化
		pnew->data = rand()%1000;
	    //开始使用共享资源，进行上锁
	    pthread_mutex_lock(&mutex);
		pnew->next = head;
		head = pnew;
		printf("======> producer:%lu, %d\n", pthread_self(), pnew->data);
		
		//使用完共享资源，上锁
		pthread_mutex_unlock(&mutex);
		//生产完成后，通知阻塞的消费者线程解除阻塞
		//该函数至少唤醒一个阻塞在该条件变量上的线程
		pthread_cond_signal(&cond);

		sleep(rand()%3);
	}
	return NULL;
}

//消费者一直消费
void* costumer(void* arg)
{
	//删除头结点
	while(1)
	{
		//开始使用共享资源，加锁
		pthread_mutex_lock(&mutex);
		if(head == NULL)
		{
			//continue;
			//使用条件变量，让线程阻塞
			//该函数，会对互斥锁解锁
			pthread_cond_wait(&cond, &mutex);
			//受到信号，解除阻塞后，该函数会对互斥锁加锁
		}
		Node* pdel = head;
		head = head->next;
		printf("======> costumer:%lu, %d\n", pthread_self(), pdel->data);
		free(pdel);
		//解锁
		pthread_mutex_unlock(&mutex);
	}
	return NULL;
}
int main(int argc, const char* argv[])
{
	//初始化互斥锁
	pthread_mutex_init(&mutex, NULL);
	//初始化条件变量
	pthread_cond_init(&cond, NULL);

	pthread_t p1, p2;

	//生产者线程
	pthread_create(&p1, NULL, producer, NULL);

	//消费者线程
	pthread_create(&p2, NULL, costumer, NULL);

	//主线程回收
	pthread_join(p1, NULL);
	pthread_join(p2, NULL);

	//销毁互斥锁，条件变量
	pthread_mutex_destroy(&mutex);
	pthread_cond_destroy(&cond);

	return 0;
}
