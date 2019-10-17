#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define MAX 10

int A[MAX][MAX], B[MAX][MAX];
long int C[MAX][MAX];
int t = 1;

void *mul_thread(void *args)
{
    int row, col, *rcArgs, k, i;
    long int return_val = 0;
    rcArgs = (int*)args;
    row = rcArgs[0];
    col = rcArgs[1];
    k = rcArgs[2];
    printf(" in thread %d %d %d\n",row, col, k);
    for(i = 0; i < k; i++)
    {
        return_val = return_val + (A[row][i] * B[i][col]);
    }
    pthread_exit((void*)return_val);
}

void accept_matrix(int M[MAX][MAX], int rows, int cols)
{
	int i, j;
	printf("\n");
	for(i=0;i<rows;i++)
	{
		for(j=0;j<cols;j++)
		{
			printf("Value at [%d][%d]: ",i+1,j+1);
			scanf("%d",&M[i][j]);
		}
	}
}

void display_matrix(int M[MAX][MAX], int rows, int cols)
{
	int i, j;
	printf("\n");
	for(i=0;i<rows;i++)
	{
		for(j=0;j<cols;j++)
		{
			printf("%d  ",M[i][j]);
		}
		printf("\n");
	}
}

int main()
{
    int rows_A, cols_A, rows_B, cols_B;
	int rcArgs[3];
	int i, j, k, *status;
    pthread_t P[MAX][MAX];
	printf("\nEnter no. of rows in matrix A: ");
	scanf("%d",&rows_A);
	printf("Enter no. of columns in matrix A: ");
	scanf("%d",&cols_A);
    printf("\nEnter no. of rows in matrix B: ");
	scanf("%d",&rows_B);
	printf("Enter no. of columns in matrix B: ");
	scanf("%d",&cols_B);
    accept_matrix(A, rows_A, cols_A);
    accept_matrix(B, rows_B, cols_B);
    for(i = 0; i < rows_A; i++)
    {
        for(j = 0; j < cols_B; j++)
        {
            rcArgs[0] = i;
            rcArgs[1] = j;
            rcArgs[2] = cols_A;
            printf("%d %d %d\n",rcArgs[0], rcArgs[1], rcArgs[2]);
            pthread_create(&P[i][j], NULL, mul_thread, rcArgs);
            sleep(3);
        }
    }
    for(i = 0; i < rows_A; i++)
    {
        for(j = 0; j < cols_B; j++)
        {
            pthread_join(P[i][j], (void**)&status);
            C[i][j] = (long int)status;
        }
    }
    display_matrix(A, rows_A, cols_A);
	display_matrix(B, rows_B, cols_B);
    printf("\n");
    for(i=0;i<rows_A;i++)
	{
		for(j=0;j<cols_B;j++)
		{
			printf("%ld  ",C[i][j]);
		}
		printf("\n");
	}
	printf("\n------------------------------------------------------\n\n");
	exit(EXIT_SUCCESS);
}
