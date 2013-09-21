/*Program to implement ls | sort using pipe() and fork() system calls*/

#include<iostream>
#include<dirent.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<cstdlib>
#include<string.h>
#include<wait.h>

#define BUFSIZE 256

void sort(char *[], int);
int compare(char * ,char *);

using namespace std;

int main()
{
	int pid, fd[2];
	char *buf[BUFSIZE];
	char buffer[BUFSIZE];
	
	if(pipe(fd)==-1)
	{
		cout<<"pipe error";
		exit(1);
	}
	
	pid=fork();
	
	
	if(pid)
	{	
		
		close(fd[1]);
		wait(NULL);
		
		int i=0,n;
		
		while((n=read(fd[0], buffer, BUFSIZE))>0)
		{	
			
			cout<<buffer<<endl;
			i++;
		}
		close(fd[0]);
		
	}
	
	else
	{	
		close(fd[0]);
		
		struct dirent *entry;
		DIR *dir;
		int i;
		dir=opendir(".");
		int count=0;  
		
		while((entry=readdir(dir)))
		{	
			if(entry->d_name[0]=='.')
				continue;
				
			buf[count]=entry->d_name;
			count++;
		}
		
		sort(buf, count);
		
		
		for(i=0;i<count;i++)
		{
			
			write(fd[1], buf[i], BUFSIZE);
		}
	

	
		closedir(dir);
		close(fd[1]);
		
	}
	
	return 0;
}


void sort(char *buf[], int count)
{	int i,j;
	char *temp;
	for(i=0;i<count;i++)
		for(j=0;j<count-1;j++)
			if(compare(buf[j],buf[j+1])>0)
			{	
				temp=buf[j];
				buf[j]=buf[j+1];
				buf[j+1]=temp;
			}
						
	return;
}

int compare(char *a,char *b)
{
	return strcasecmp(a,b);
}



