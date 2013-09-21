#include<stdio.h>			
#include<dirent.h>			//contains definitions of struct dirent and fns opendir(), readdir() etc
#include<sys/stat.h>			//contains struct stat, and stat fns
#include<errno.h>			//for printing error msgs corresponding to different errno values

void fsize(struct stat *);
inline void prnsize(off_t);

int main(int argc, char * argv[])
{
	if(argc!=2)
	{
		printf("Format : %s <filename>\n", argv[0]);
		return 1;
	}
	
	char *filename;
	struct stat fileinfo;
	
	filename = argv[1];
		
	if(stat(filename, &fileinfo)==-1)
	{
		perror("stat");
		exit(1);
	}
	
	if(!S_ISDIR(fileinfo.st_mode))				//if not a directory, then simply print file size
	{
		fsize(&fileinfo);
		printf("\n");
		return 0;
	}	
	
	DIR *dir;						//if its a directory do a walk and print file names
	struct dirent *entry;
	
	dir=opendir(filename);
	
	if(chdir(filename)==-1)				//change working directory of process to the directory to be walked
	{
		perror("chdir");
		exit(1);
	}
	
	while((entry=readdir(dir)))
	{	
		if(stat(entry->d_name, &fileinfo)==-1)
		{
			perror("stat");
			printf("%s\n", entry->d_name);
		}	
		
		fsize(&fileinfo);
		printf("\t%s\n", entry->d_name);
		
	}
	
	closedir(dir);
	
		
	return 0;
}


void fsize(struct stat * fileinfo)
{
		
	prnsize(fileinfo->st_size);
	return;
}
	
	
inline void prnsize(off_t size)
{
	printf("%ld", (long) size);
}	
