#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
#define max 10

int readCount = 0, var = 1;
sem_t wsem;
pthread_mutex_t lock;

void *reader(void *arg)
{
    int reader = *(int*) arg;
    while(1)
    {
        pthread_mutex_lock(&lock);
            readCount++;
            if(readCount == 1)
                sem_wait(&wsem);
        pthread_mutex_unlock(&lock);
            printf("Value read by reader %d is %d", reader, var);
        pthread_mutex_lock(&lock);
            readCount--;
            if(readCount == 0)
                sem_post(&wsem);
        pthread_mutex_unlock(&lock);
    }
}

void *writer(void *arg)
{
    int writer = *(int*) arg;
    while(1)
    {
        sem_wait(&wsem);
            var++;
            printf("Value updated by writer %d to value %d", writer, var);
        sem_post(&wsem);
    }
}

int main()
{
	int read,write,i;

	if(sem_init(&writer,0,1) != 0)
	{
		printf("\nSEMAPHORE INITIALISATION FAILED!\n");
		exit(0);
	}

	if(pthread_mutex_init(&mutex,NULL) != 0)
	{
		printf("\nSEMAPHORE CREATION FAILED!\n");
		exit(0);
	}

	printf("\nEnter the number of readers:");
	scanf("%d",&read);
	printf("\nEnter the number of writers:");
	scanf("%d",&write);

	pthread_t reads[max], writes[max];
	for(i=0; i<write; i++)
	{
		if(pthread_create(&writes[i],NULL,writerFunc,NULL) != 0)
		{
			printf("\nWriter thread no %d creation failed!",i+1);
		}
		else
		{
			printf("\n\nWriter thread no %d created!",i+1);
		}
	}

	for(i=0; i<read; i++)
	{
		if(pthread_create(&reads[i],NULL,readerFunc,NULL) != 0)
		{
			printf("\nReader thread no %d creation failed!",i+1);
		}
		else
		{
			printf("\n\nReader thread no %d created!",i+1);
		}
	}

	for(i=0; i<read; i++)
	{
		if(pthread_join(reads[i],NULL) != 0)
			printf("\nReader thread no %d failed!",i+1);
	}

	for(i=0; i<write; i++)
	{
		if(pthread_join(writes[i],NULL) != 0)
			printf("\nWriter thread no %d failed!",i+1);
	}
}
