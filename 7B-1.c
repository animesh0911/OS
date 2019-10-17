#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main()
{
    int fd;
    char *myfifo = "/Users/Anni/myfifo";
    int i = 0;
    mkfifo(myfifo, 0666);
    char arr1[80], arr2[80];
    while(1)
    {
        fd = open(myfifo, O_WRONLY);
        printf("\nFile 1 to write \n");
        gets(arr1);
        write(fd, arr1, strlen(arr1)+1);
        close(fd);
        printf("\nWaiting for file 2 to write \n");
        wait(NULL);
        fd = open(myfifo, O_RDONLY);
        read(fd, arr2, sizeof(arr2));
        printf("\nUser 2 : %s \n",arr2);
        close(fd);
    }
    return 0;
}
