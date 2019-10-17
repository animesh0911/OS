#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
    int fd;
    char *myfifo = "/Users/Anni/myfifo";
    int char_count;
    int word_count;
    int sent_count;
    int i;
    mkfifo(myfifo, 0666);
    char str1[80], str2[80];
    while(1)
    {
        printf("\nWaiting for file1 to write \n");
        wait(NULL);
        fd = open(myfifo,O_RDONLY);
        read(fd,str1,80);
        printf("\nUser1: %s \n", str1);
		i = 0;
		char_count = 0;
		word_count = 1;
		sent_count = 1;
		while(str1[i] != '\0')
		{
			if((str1[i] >= 'a' && str1[i] <= 'z') || (str1[i] >= 'A' && str1[i] <= 'Z') || (str1[i] >= '0' && str1[i] <= '9'))
				char_count++;
			if(str1[i] == ' ')
				word_count++;
			if(str1[i] == '.' && str1[i+1] == ' ')
				sent_count++;
			i++;
		}
		close(fd);
        sprintf(str2,"\nNumber of characters = %d \n Number of words = %d \n Number of sentences = %d \n",char_count, word_count, sent_count);
        fd = open(myfifo, O_WRONLY);
        write(fd,str2,strlen(str2)+1);
        close(fd);
    }
    return 0;
}
