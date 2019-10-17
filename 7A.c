#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    int pipe1[2], pipe2[2];
    int returnstatus1, returnstatus2;
    int pid;
    char pipe1writemessage[20];
    char pipe2writemessage[20];
    char readmessage[20];
    FILE *fp;
    char ch;
    int i = 0;
    strcpy(pipe1writemessage,argv[1]);
    returnstatus1 = pipe(pipe1);
    returnstatus2 = pipe(pipe2);
    pid = fork();
    if(pid != 0)
    {
        close(pipe1[0]);
        close(pipe2[1]);
        printf("In Parent: Writing to pipe 1 – Message is :: %s\n", pipe1writemessage);
        write(pipe1[1],pipe1writemessage,sizeof(pipe1writemessage));
        read(pipe2[0], readmessage, sizeof(readmessage));
        printf("In Parent: Reading from pipe 2 – Message is :: %s\n", readmessage);
    }
    else
    {
        close(pipe1[1]);
        close(pipe2[0]);
        read(pipe1[0], readmessage, sizeof(readmessage));
        fp = fopen(readmessage, "r");
        ch = fgetc(fp);
        while(ch != EOF)
        {
            pipe2writemessage[i] = ch;
            i++;
            ch = fgetc(fp);
        }
        printf("In Child: Reading from pipe 1 – Message is :: %s\n", readmessage);
        printf("In Child: Writing to pipe 2 – Message is :: %s\n", pipe2writemessage);
        write(pipe2[1], pipe2writemessage, sizeof(pipe2writemessage));
    }
    return 0;
}
