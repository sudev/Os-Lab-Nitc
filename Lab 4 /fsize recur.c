#include<fcntl.h>
#include<stdlib.h>
#include<string.h>
#include "./string.c"
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<dirent.h>
void fsize(char *path)
{
	int f;
	char buf[256],buf2[8];
	DIR *dr;
	dr=opendir(path);
	if(dr==NULL)
	{
		f = open(path,O_RDONLY);
		if(f<0)
		{
			perror("Path : ");
			exit(1);
		}
		else
		{
			int size = lseek(f,0, SEEK_END);
			strcpy(buf,path);
			strcat(buf,"\t\t");
			i2a(size,buf2);
			strcat(buf,buf2);
			strcat(buf,"\n");
			write(1,buf,strlen(buf));
			close(f);
 		}
	}
	else
	{
		struct dirent* content;
		while(content=readdir(dr))
		{
			char fp[300];
			strcpy(fp,path);
			strcat(fp,"/");
			strcat(fp,content->d_name);
			if(strcmp(content->d_name,"..")!=0 && strcmp(content->d_name,".")!=0)
			{
				fsize(fp);			
			}
		}	
		closedir(dr);
	}
}
int main(int argc, char *argv[])
{
	if(argc < 2)
	{
		write(1,"Agruments required\n",19);
		return 0;
	}
	fsize(argv[1]);	
}
