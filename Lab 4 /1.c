//write a program to read n characters from postion 
// k from a text file 
#include <stdio.h>
#include <sys/stat.h>
#include <errno.h>
#include<fcntl.h>
#include<unistd.h>
int main(int argc,char * argv[])
{
  
  //check for the required arguments  
  if ( argc != 4)
    {
      printf(" %s filename start lines ",argv[0]);
    }
  //taking values as integers   
  int start = atoi(argv[2]);
  int lines = atoi(argv[3]);
  int fd;
  char filename=argv[1];
  //check the fd status if it fails returns -1
  if((fd=open(argv[1], O_RDONLY))==-1)
	{
	  fprintf(stderr, "Error in opening file %s\n", argv[1]);
	  exit(1);
	}
  //seek from the begining of the file to sleeek_set to start 
  if((lseek(fd, start, SEEK_SET))!=start)
		perror("lseek");
  //the pointer will be @ start now 
  //read and write the bytes from now 
  char buffer[128];
  
  while(lines>128)
	{
	
	while(read(fd, buffer, 128)>0)
	  {
	  printf("%s", buffer);
	  }
	lines=lines - 128;
	}
	
	if(read(fd, buffer, lines)>0)
	{
	write(1, buffer, lines);
	}
			
  return 0;
}
