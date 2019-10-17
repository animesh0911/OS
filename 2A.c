#include <stdio.h>
void bubble_sort_asc(int A[], int n);
void bubble_sort_dsc(int A[], int n);

void bubble_sort_asc(int A[], int n)
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

void bubble_sort_dsc(int A[], int n)
{
    int i, j, temp;
    for(i = 0; i < n - 1; i++)
    {
        for(j = i + 1; j < n; j++)
        {
            if(A[i] < A[j])
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
    int *A, n, i, pid;
    printf("\n Enter the number of digits to be sorted \n");
    scanf("%d", &n);
    A = (int*)malloc((sizeof(int)*n));
    printf("\n Enter the digits \n");
    for(i = 0; i < n; i++)
    {
        scanf("%d", &A[i]);
    }
    printf("\n Before forking \n");
    pid = fork();
    if(pid != 0)
    {

        printf("\n Parent process is on \n ");
        printf("\n Sorting integers in asc \n");
        bubble_sort_asc(A, n);
        wait();
        printf("\n Sorted integers are \n");
        for(i = 0; i < n; i++)
        {
            printf("%d ",A[i]);
        }
        printf("\n Parent exited \n");
        exit(0);
    }
    else
    {
        printf("\n Child process is on \n ");
        printf("\n Sorting integers in dsc \n");
        bubble_sort_dsc(A, n);
        printf("\n Sorted integers are \n");
        for(i = 0; i < n; i++)
        {
            printf("%d ",A[i]);
        }
        printf("\n Child exited \n");
        exit(0);
    }
}
