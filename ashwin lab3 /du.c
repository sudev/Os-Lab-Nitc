#include<fcntl.h>					//required for file operations like open(), stat() etc.
#include<dirent.h>					//for traversing directories. contains defn of struct dirent and fns opendir, readdir etc.
#include<stdio.h>						
#include<sys/stat.h>					//contains macro S_ISDIR	
#include<string.h>					//contains string operations strcpy and strcat
#include<errno.h>


void prnsize(off_t);					//fn to print the size passed as argument
off_t dir_du(char *, char *);				//function to traverse a directory and return its size


int main(int argc, char* argv[])				
{
	struct stat file;						//struct to hold file info
	off_t size;							//datatype for handling sizes
	char path[100];						
	
	if(argc==1)
	{
		size=dir_du(".", ".");
		return;
	}
	
	if(argc!=2)
	{
		printf("Format : %s <filename>\n", argv[0]);
		exit(1);
	}
	
	if(stat(argv[1], &file)<0)						//stat fn returns -1 on failure.
	{
		fprintf(stderr, "Error opening file %s \n", argv[1]);
		exit(1);
	}
	
	if(!S_ISDIR(file.st_mode))						//if argument is not directory, print size of the file only.
	{
		prnsize((512*file.st_blocks)/1024);
		printf("\t%s\n", argv[1]);
	}
	
	else 									//else traverse the directory and prints its size.
		size=dir_du(argv[1], argv[1]);
		
	return 0;
}


void prnsize(off_t size)
{
	printf("%ld", (long)size);						//typecast off_t to long
	return;
}


off_t dir_du(char * dirname, char *path)					//takes current directory name and its path as arguments
{
	off_t dirsize=0;							//variable holding current directory's size
	DIR *dir;
	struct dirent *direntry;						//variable to store the details of each directory entry as it is read.
	struct stat entryinfo;							//variable to store file details(contains off_t value) of each directory entry.
		
	dir=opendir(dirname);							//open dirname directory and store stream info in variable dir.
	
	int fd = open(dirname, O_RDONLY);
	
	if(fstat(fd, &entryinfo)==-1)					//get file info of given directory entry, fn returns -1 on failure.
		{
			fprintf(stderr, "Error getting info for file %s\n", direntry->d_name);
			exit(1);
		}
		
		
	dirsize+=entryinfo.st_blocks*512;
	
	close(fd);	
		
	if(chdir(dirname)==-1)							//change working directory of program to dirname.
	{
		fprintf(stderr, "Error switching to directory %s\n", dirname);
		exit(1);
	}
		
	while((direntry=readdir(dir))!=NULL)					//read directory entries from dir one by one
	{	
		fd=open(direntry->d_name, O_RDONLY);
		
		if(fstat(fd, &entryinfo)==-1)			//get file info of given directory entry, fn returns -1 on failure.
		{
			fprintf(stderr, "Error getting info for file %s\n", direntry->d_name);
			exit(1);
		}
		
		if(!S_ISDIR(entryinfo.st_mode))				//if current entry is not a directory in itself, simply add its size
			dirsize+=entryinfo.st_blocks*512;
		else if((strcmp(direntry->d_name, "..")==0)||(strcmp(direntry->d_name, ".")==0))		//skip entry if it is . or ..
			continue;
		else
		{	
			
			char temp[1000];
			strcpy(temp, path);			
			dirsize+=dir_du(direntry->d_name, strcat(strcat(temp, "/"), direntry->d_name));		/*if the directory entry is a directory by itself
														  then get its size by recursively calling the
														  dir_du fn on it. to get path of the directory,
														  first copy path to a string variable temp. then
														  concatenate a / and the directory name.
														  DO NOT directly concatenate to path as this 
														  result in random values.*/
													 
		}
		
		close(fd);
			
	}
	
	prnsize(dirsize/1024);
	printf("\t%s\n",path);
	
	if(chdir("..")==-1)								/*after current directory is fully traversed and its info printed
											  return to its parent directory. */
	{
		fprintf(stderr, "Error switching to parent directory %s\n", dirname);
		exit(1);
	}
	closedir(dir);								//close the directory stream to clear memory.
	return dirsize;
}
			
		
		
	
	
