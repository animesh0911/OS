#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>

typedef struct
{
    char str[50];
    int flag;
}structure;

int main()
{
        key_t key1 = ftok("/Users/Anni/Practicals/",75);
        if(key1 == -1)
        {
            printf("Error while creating key \n");
            exit(0);
        }
        int shmid1 = shmget(key1, 1024, 0666|IPC_CREAT);
        if(shmid1 < 0)
        {
            printf("Error while creating shared memory\n");
            exit(0);
        }
        structure *s1 = (structure*)shmat(shmid1, (void*)0, 0);


        key_t key2 = ftok("/Users/Anni/Practicals/",85);
        if(key2 == -1)
        {
            printf("Error while creating key \n");
            exit(0);
        }
        int shmid2 = shmget(key2, 1024, 0666|IPC_CREAT);
        if(shmid2 < 0)
        {
            printf("Error while creating shared memory\n");
            exit(0);
        }
        structure *s2 = (structure*)shmat(shmid2, (void*)0, 0);

        
        while(1)
        {
            printf("\nEnter the string:");
            gets(s1->str);
            s1->flag = 1;
            printf("\nData written in memory: %s\n",s1->str);
            printf("\nShared memory address: %X\n",shmid1);

            if(s2->flag == 1)
            {
                printf("\nData read from memory: %s\n",s2->str);
                printf("\nShared memory address: %X\n",shmid2 );
                s2->flag = 0;
            }
        }
        shmdt(s1);
        shmctl(shmid1, IPC_RMID, NULL);
        shmdt(s2);
        shmctl(shmid2, IPC_RMID, NULL);
}
