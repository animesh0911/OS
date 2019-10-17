#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

void bubble(int A[], int n)
{
    int i, j, temp;
    for(i = 0; i < n - 1; i++)
    {
        for(j = i + 1; j < n; j++)
        {
            if(A[i] > A[j])
            {
                temp = A[i];
                A[i] = A[j];
                A[j] = temp;
            }
        }
    }
}

int main()
{
    int A[15], n, i, id;
    char *arg[15], str[15];
    printf("\n Before forking\n");
	printf("\n Enter the number of integers to be sorted :- \n");
	scanf("%d",&n);
	printf("\n Enter the integers :- \n");
	for(i=0;i<n;i++)
	{
		scanf("%d",&A[i]);
	}
	printf("\n Entered integers are :- \n");
	for(i=0;i<n;i++)
	{
		printf("%d ",A[i]);
	}
	printf("\n Sorting array in ascending order \n");
	bubble(A,n);
	printf("\n Invoking fork \n");
	id=fork();
    if(id != 0)
    {
        printf("\n in parent \n");
        printf("\n Parent's parent process id is %d \n",getppid());
        printf("\n Parent process id is %d \n",getpid());
        wait(NULL);
        printf("\n Back to parent process \n");
        printf("\n Parent process exited \n");
        exit(0);
    }
    else
    {
        printf("\n in child \n");
        printf("\n Child's parent process id is %d \n",getppid());
        printf("\n Child process id is %d \n",getpid());
        for(i = 0; i < n; i++)
        {
            printf("%d ", A[i]);
            sprintf(str,"%d",A[i]);
            arg[i] = (char*)malloc(sizeof(str));
            strcpy(arg[i], str);
        }
        arg[i] = NULL;
        printf(" \n------------Switching to new program for searching------------- \n");
        execve("./2B-2",arg,NULL);
        printf(" \nChild process exited \n");
		exit(0);
    }
}
