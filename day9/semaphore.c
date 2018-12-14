#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<string.h>
#include<semaphore.h>
#include<pthread.h>

sem_t produce_sem;
sem_t custom_sem;

typedef struct node
{
	int data;
	struct node* next;
}Node;

Node* head = NULL;

//生产者
void* produce(void *arg)
{
	while(1)
	{
		sem_wait(&produce_sem);
		Node *node = (Node*)malloc(sizeof(Node));
		node->data = rand()%1000;
		node->next = head;
		head = node;
		printf("+++++生产者：%lu, %d\n", pthread_self(), node->data);
		sem_post(&custom_sem);

		sleep(rand()%5);
	}
	return NULL;
}

//消费者
void* customer(void* arg)
{
	while(1)
	{
		sem_wait(&custom_sem);  //=0就阻塞，不为0就删除节点
		Node* pNode = head;
		head = head->next;
		printf("+++++消费者：%lu, %d\n", pthread_self(), pNode->data);
		free(pNode);
		sem_post(&produce_sem);
		sleep(rand()%5); 
	}
	reutrn NULL;
}
int main(int argc, const char* argv[])
{
	int i;
	pthread_t pthid[2];
	//给生产者分配2个资源
	sem_init(&produce_sem, 0, 2);
	//给消费者不分配资源，先阻塞
	sem_init(&custom_sem, 0, 0);

	pthread_create(&pthid[0], NULL, produce, NULL);
	pthread_create(&pthid[1], NULL, customer, NULL);

	for(i = 0;i < 2; ++i)
	{
		pthread_join(pthid[i], NULL);
	}

	//销毁信号量
	sem_destroy(&produce_sem);
	sem_destroy(&custom_sem);

	return 0;
}
