//PROGRAM TO Implement the ls | sort using fork and
// pipe functionn 

#include <iostream>
#include <wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <fctnl.h>
#include<cstdlib>

void bublesort(char *[], int);
using namespace std;

int main(int argc,char * argv[])
{
  int forkstate, fd[2];
  char *buf[128], buffer[128];
  
  //pipe success check 
  if(pipe(fd)<0)
  {
    cout<<"cant create pipe ";
    exit(1);
  }
  forkstate=fork();
  if(forkstate)
  {	
  //close the read end 
    close(fd[1]);
    //wait for the child to process 
    wait(NULL);
    int count=0;
    while((/*n=*/read(fd[0], buffer, 128))>0)
    {	
    cout<<buffer<<endl;
    count++;
    }
    //close pipe end 
    close(fd[0]);
  }
  else
  {	
  //close the end which is not going to be used 
  close(fd[0]);
  struct dirent *entry;
  DIR *curdir;
  int count;
  dir=opendir(".");
  int i=0;
  while((entry=readdir(curdir)))
  {	
  if(entry->d_name[0]=='.')
  continue;
  buf[i]=entry->d_name;
  i++;
  }
  bubbblesort(buf, count);
  for(count=0;count<i;count++)
  {
  write(fd[1], buf[count],128);
  }
  closedir(curdir);
  close(fd[1]);
  }
  return 0;
}


//implement bubbble sort to sort the given list 
void bubblesort(cahr *buf[], int i)
{
  int j,k;
  char *t;
  for(j=0;j<i; j++)
    for(k=0;k<i-1;k++) 
      if((strcasecmp(buf[k],buf[k+1]))>0)
      {
	//swap
	t=buf[k];
	buf[k]=buf[k+1];
	buf[k+1]=t;
      }
   return;
}