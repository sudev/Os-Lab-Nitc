// ls -l using stat()

#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include<stdio.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/types.h>
#include <pwd.h>
#include<string.h>
#include <grp.h>
#include<time.h>
int main(int argc, char *argv[]) 
{
	struct stat fileStat;
	DIR* dty;
	char path[200];
	strcpy(path, argc<2?".":argv[1]);
	dty = opendir(path);
	struct dirent* content;
	while(content=readdir(dty))
	{
		if(strcmp(content->d_name,"..")!=0 && strcmp(content->d_name,".")!=0 && content->d_name[0]!='.')
		{   	

			char fp[300];
			sprintf(fp,"%s/%s",path,content->d_name);
			stat(fp,&fileStat);
			printf( (S_ISDIR(fileStat.st_mode)) ? "d" : "-");
			printf( (fileStat.st_mode & S_IRUSR) ? "r" : "-");
			printf( (fileStat.st_mode & S_IWUSR) ? "w" : "-");
			printf( (fileStat.st_mode & S_IXUSR) ? "x" : "-");
			printf( (fileStat.st_mode & S_IRGRP) ? "r" : "-");
			printf( (fileStat.st_mode & S_IWGRP) ? "w" : "-");
			printf( (fileStat.st_mode & S_IXGRP) ? "x" : "-");
			printf( (fileStat.st_mode & S_IROTH) ? "r" : "-");
			printf( (fileStat.st_mode & S_IWOTH) ? "w" : "-");
			printf( (fileStat.st_mode & S_IXOTH) ? "x" : "-");
			
			printf(" %d",fileStat.st_nlink);
			
			printf(" %lu",(long)fileStat.st_size);
			
			struct passwd *userinfo;
			userinfo = getpwuid(fileStat.st_uid);
			printf(" %s",userinfo->pw_name);				
			
			struct group *groupinfo;
			groupinfo =  getgrgid(fileStat.st_gid);
			printf(" %s",groupinfo->gr_name);
			
			struct tm* modtime;
			modtime = localtime(&fileStat.st_mtime);

			char *t = malloc(sizeof(char)*20);
			strftime(t,20,"%Y-%m-%d %H:%M", modtime);
			printf(" %s", t);
			
			printf(" %s \n", content->d_name);				
		}		
	}	
	closedir(dty);
}

