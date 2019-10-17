#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
#define buffer_size 5

typedef struct
{
    int in, out;
    sem_t full, empty;
    pthread_mutex_t mutex;
    int buffer[buffer_size];
}BUFFER;

BUFFER b;
int item = 1;

void display_buffer(int buffer[buffer_size])
{
    int i = 0;
    for(i = 0; i < buffer_size; i++)
    {
        printf("%d ",buffer[i]);
    }
    printf("\n\n");
}

void *producer(void *arg)
{
    int i, r, value;
    i = *(int*)arg;
    while(1)
    {
        sem_wait(&b.empty);
        sem_getvalue(&b.empty, &value);
        if(value == 0)
        {
            printf("Buffer Full\n");
        }
        pthread_mutex_lock(&b.mutex);
        printf("producer %d produced item %d \n",i,item);
        b.buffer[(b.in++)%buffer_size] = item++;
        display_buffer(b.buffer);
        pthread_mutex_unlock(&b.mutex);
        sem_post(&b.full);
	sleep(3);
    }
}

void *consumer(void *arg)
{
    int i, r, value, consumed;
    i = *(int*)arg;
    while(1)
    {
        sem_wait(&b.full);
        sem_getvalue(&b.full, &value);
        if(value == buffer_size)
        {
            printf("Buffer Empty\n");
        }
        pthread_mutex_lock(&b.mutex);
        consumed = b.buffer[(b.out)%buffer_size];
        b.buffer[(b.out++)%buffer_size] = 0;
        printf("consumer %d consumed item %d\n",i,consumed);
        display_buffer(b.buffer);
        pthread_mutex_unlock(&b.mutex);
        sem_post(&b.empty);
	sleep(1);
    }
}

void init()
{
    b.in, b.out = 0;
    sem_init(&b.full,0,0);
    sem_init(&b.empty,0,buffer_size);
    pthread_mutex_init(&b.mutex,NULL);
}

int main()
{
    int i, np, nc;
    int c[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    pthread_t pro[buffer_size], con[buffer_size];
    printf("Enter number of producers :: ");
	scanf("%d",&np);
	printf("Enter number of consumers :: ");
	scanf("%d",&nc);
	init();
    for(i = 0; i < buffer_size; i++)
    {
	b.buffer[i] = 0;
    }
    for(i = 0; i < np; i++)
    {
        pthread_create(&pro[i], NULL, *producer, &c[i]);
        printf("\tThread created for producer %d-------------------\n",i+1);
    }
    for(i = 0; i<nc; i++)
	{
		pthread_create(&con[i], NULL, *consumer, &c[i]);
		printf("-Thread created for consumer %d-------------------\n",i+1);
	}
	for(i = 0; i<np; i++)
	{
		pthread_join(pro[i], NULL);
		printf("\tThread joined for producer %d --------------------\n",i+1);
	}
	for(i = 0; i<nc; i++)
	{
		pthread_join(con[i], NULL);
		printf("Thread joined for consumer %d ---------------------\n",i+1);
	}
	return 0;
}
