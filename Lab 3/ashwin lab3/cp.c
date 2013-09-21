/*program to implement cp command. program takes as arguemnts a source file name and a destination file name. 
  If the destination file doesnt exist, it is created. If it exists, user is asked if it needs to be overwritten. 
  If not, program exits.*/

#include<fcntl.h>						//required for file control system calls
#include<stdio.h>

#define BUFSIZE 1024

int main(int argc, char *argv[])
{
	if(argc!=3)								//pgm requires source file name and destination file name as arguments
	{
		fprintf(stderr, "format : %s sourcefile destfile\n", argv[0]);
		exit(1);
	}

	
	char *src = argv[1];
	char *dest = argv[2];

	int rfd, wfd;							//read and write file descriptors
	
	if((rfd=open(src, O_RDONLY))==-1)				//open() returns -1 on failure, descriptor of open file if successful.
	{
		fprintf(stderr, "Error opening source file %s\n", argv[1]);
		exit(1);
	}
	
	char choice;
	
	if((wfd=open(dest, O_WRONLY | O_CREAT | O_EXCL, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH))==-1)		/*open fails if file already exists. if not
														  file is created with read and write permissions
														  for owner and read permission for group
														  and other users*/
	{
		printf("File already exists! overwrite?(y/n) : ");
		scanf("%c", &choice);
		
		if(choice=='n' || choice=='N')
		{
			printf("Exiting.\n");
			exit(1);
		}
		
		if((wfd=open(dest, O_WRONLY))==-1)				//if user wants file to be overwritten, file is opened in write only mode.
		{
			fprintf(stderr, "Error opening output file.\n");
			exit(1);
		}	
		
	}
	
	char buffer[BUFSIZE];
	int no_chars;
	
	while((no_chars=read(rfd, buffer, BUFSIZE))>0)				//read returns number of characters read from file. 
	{
		if(write(wfd, buffer, no_chars)!=no_chars)			//write returns number of characters written to file.
		{
			fprintf(stderr, "Error in writing to %s\n", dest);
			exit(1);
		}
	}
		
	close(rfd);
	close(wfd);
	
	return 0;
}
