#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
#include <sys/types.h>

#define thinking 0
#define hungry 1
#define eating 2
#define N 5
#define left (N+i-1)%N
#define right (i+1)%N

sem_t lock;
sem_t s[N];
int phil[N] = {0, 1, 2, 3, 4};
int state[N], chances[N];
pthread_t p[N];

void test(int i)
{
    if(state[i] == hungry && state[left] != eating && state[right] != eating)
    {
        printf("Philosoher %d has taken forks \n",i);
        printf("Philosoher %d is now eating \n",i);
        state[i] = eating;
        chances[i]++;
        printf("Eating Chances...\n\n");
		for(int j=0;j<N;j++)
			printf("\t %d",chances[j]);
		printf("\n");
        sleep(2);
        sem_post(&s[i]);
    }
}

void take_fork(int i)
{
    sem_wait(&lock);
    state[i] = hungry;
    printf("Philosoher %d is now hungry \n",i);
    test(i);
    sem_post(&lock);
    sem_wait(&s[i]);
    sleep(1);
}

void put_fork(int i)
{
    sem_wait(&lock);
    state[i] = thinking;
    printf("Philosopher %d is now putting forks down \n",i);
    printf("Philosopher %d is now thinking \n",i);
    test(left);
    test(right);
    sem_post(&lock);
}

void *philosopher(void *arg)
{
    int i;
    i = *(int*)arg;
    printf("Philosopher %d has arrived at the table \n", i);
    printf("Philosopher %d is now thinking \n", i);
    while(1)
    {
        take_fork(i);
        sleep(2);
        put_fork(i);
    }
}

void init()
{
    int i;
    sem_init(&lock, 0, 1);
    for(i = 0; i < N; i++)
    {
        sem_init(&s[i], 0, 0);
    }
    for(i = 0; i < N; i++)
    {
        chances[i] = 0;
    }
}

int main()
{
    int i;
    init();
    for(i = 0; i < N; i++)
    {
        pthread_create(&p[i], NULL, philosopher, &phil[i]);
    }
    for(i = 0; i < N; i++)
    {
        pthread_join(p[i], NULL);
    }
}

