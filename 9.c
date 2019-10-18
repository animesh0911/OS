#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

typedef struct Student {
	int roll;
	char name[20];
	float marks;
	int class;
}Student;

char *dataName;

void createData() {
	int exists = access(dataName,F_OK);
	if(exists == 0)
		printf("\nDATABASE ALREADY EXISTS!\n");
	else {
		int fd = open(dataName,O_CREAT);
		if(fd < 0) {
			printf("\nERROR IN CREATING THE DATABASE!");
			exit(0);
		}
		else
			printf("\nDATABASE CREATED SUCCESSFULLY!");
		close(fd);
	}
}

void writeData() {
	Student s;
	printf("\nENTER ROLL NO:");
	scanf("%d",&s.roll);
	printf("\nENTER NAME:");
	scanf("%s",s.name);
	printf("\nENTER MARKS:");
	scanf("%f",&s.marks);
	printf("\nENTER CLASS:");
	scanf("%d",&s.class);

	int fd = open(dataName,O_WRONLY | O_APPEND);
	if(fd < 0){
		printf("\nERROR IN WRITING THE RECORD!\n");
		exit(0);
	}
	else {
		write(fd,&s,sizeof(s));
		printf("\nRECORD WRITTEN SUCCESSFULLY!\n");
	}
	close(fd);
}

void readData() {
	Student s;
	int fd = open(dataName,O_RDONLY);
	if(fd < 0) {
		printf("\nERROR IN READING THE DATABASE!");
		exit(0);
	}
	else {
		printf("\nROLL \tNAME \tMARKS \t\tCLASS");
		while(read(fd,&s,sizeof(s)))
			printf("\n%d \t%s \t%f \t%d",s.roll,s.name,s.marks,s.class);
	}
	close(fd);
}

void searchData(int key) {
	Student s;
	int flag, fd = open(dataName, O_RDONLY);
	if(fd < 0) {
		printf("\nERROR IN READING THE FILE!");
		exit(0);
	}
	else {
		while(read(fd,&s,sizeof(s))) {
			if(s.roll == key) {
				printf("\nRECORD FOUND!");
				printf("\n%d \t%s \t%f \t%d",s.roll,s.name,s.marks,s.class);
				flag = 1;
			}
		}
	}
	if(flag == 0)
		printf("\nRECORD NOT FOUND!");
	close(fd);
}

void deleteData(int key) {
	char *tmp = "temp";
	Student s;
	int fd1 = open(dataName, O_RDONLY);
	int fd2 = open(tmp, O_RDWR | O_CREAT, 0777);
	if(fd1 < 0) {
		printf("\nERROR IN READING THE FILE!");
		exit(0);
	}

	while(read(fd1, &s, sizeof(s))) {
		if(s.roll != key) {
			write(fd2, &s, sizeof(s));
		}
		else {

		}
	}
	close(fd1);
	close(fd2);
	remove(dataName);
	rename(tmp,dataName);
}

void modifyData(int key) {
	char *tmp = "temp";
	Student s1, s2;
	int fd1 = open(dataName, O_RDONLY);
	int fd2 = open(tmp, O_RDWR | O_CREAT, 0777);
	if(fd1 < 0) {
		printf("\nERROR IN READING THE FILE!");
		exit(0);
	}
	while(read(fd1, &s1, sizeof(s1))) {
		if(s1.roll != key)
			write(fd2, &s1, sizeof(s1));
		else {
			printf("\nNEW ROLL NO:");
			scanf("%d",&s2.roll);
			printf("\nNEW NAME:");
			scanf("%s",s2.name);
			printf("\nNEW MARKS:");
			scanf("%f",&s2.marks);
			printf("\nNEW CLASS:");
			scanf("%d",&s2.class);
			write(fd2, &s2, sizeof(s2));
		}
	}
	close(fd1);
	close(fd2);
	remove(dataName);
	rename(tmp,dataName);
}

int main() {
	int ch, key;
	Student s;
	char fileName[20];
	while(1) {
		printf("\n\n---STUDENTS DATABASE IN FILES---\n");
		printf("\n1. CREATE DATABASE: \n2. INSERT RECORDS: \n3. DISPLAY RECORDS: \n4. SEARCH: \n5. DELETE: \n6. MODIFY: \n7. EXIT\n\nENTER YOUR CHOICE:");
		scanf("%d",&ch);
		switch(ch) {
			case 1:
				printf("\nENTER DATABASE NAME:");
				scanf("%s",fileName);
				dataName = fileName;
				createData();
				break;

			case 2:
				writeData();
				break;

			case 3:
				readData();
				break;

			case 4:
				printf("\nENTER A ROLL NO:");
				scanf("%d",&key);
				searchData(key);
				break;

			case 5:
				printf("\nENTER A ROLL NO:");
				scanf("%d",&key);
				deleteData(key);
				break;

			case 6:
				printf("\nENTER A ROLL NO:");
				scanf("%d",&key);
				modifyData(key);
				break;

			case 7:
				return 0;

			default:
			printf("\n\nENTER A CHOICE BETWEEN 1 TO 7!");
		}
	}
}
