#include<fcntl.h>
#include<stdio.h>
#include<unistd.h>

#define BUFSIZE 1024


int main(int argc, char * argv[])
{
	if (argc!=4)
	{
		printf("format : %s <filename> <no_of_characters> <file_position>\n", argv[0]);
		exit(1);
	}
	
	int fd, no_chars, fp, red;
	
	no_chars=atoi(argv[2]);
	fp=atoi(argv[3]);
	
	printf("%d\t%d\n", no_chars, fp);
	
	
	if((fd=open(argv[1], O_RDONLY))==-1)
	{
		fprintf(stderr, "Error opening file %s\n", argv[1]);
		exit(1);
	}
	
	
	if((lseek(fd, fp, SEEK_SET))!=fp)
		perror("lseek");
	
	char buffer[BUFSIZE];
	
	while(no_chars>BUFSIZE)
	{
	
		while(read(fd, buffer, BUFSIZE)>0)
		{
			printf("%s", buffer);
		}
		
		no_chars-=BUFSIZE;
	}
	
	if(read(fd, buffer, no_chars)>0)
	{
		write(1, buffer, no_chars);
	}
			
	return 0;
}
	
