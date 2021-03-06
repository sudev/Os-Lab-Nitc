#include <stdio.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>

void fsize(struct stat *);
inline void printsiz(off_t);

int main(int arg,char * argv[])
{
  if (arg!=2)
  {
    printf(" Please check this format :: %s file/foldername",argv[0]);
    return 1;
  }
  //using dirent we use DIR , funtions 
  int ch=0,flg=0;
  printf("/n1.Question 2/n2.Question 3/n");
  scanf("%d",&flg);  
  DIR *curdir;
  
  //fname and stat to store deatails of files 
  char *fname;
  fname = argv[1];
  struct stat fileinfo;
  //existence check -1 is error
  
  if(stat(fname, &fileinfo)==-1)
  {
    perror("stat");
    exit(1);
  }
  //check for directory 
  if (!S_ISDIR(fileinfo.st_mode))
  {
    if(flg==1)
    {
    fsize(&fileinfo);
    }
    return 0;
  }
  //open directory 
  curdir=opendir(fname);
  struct dirent *entry;
  if(chdir(fname)<0)
  {
    perror("chdir");
    exit(1);
  }
  while((entry=readdir(curdir)))
  {	
  //check for each directory permission to read / error
  if(stat(entry->d_name, &fileinfo)==-1)
  {
    perror("stat");
    printf(" %s \n ", entry->d_name);
  }
  if (flg==1)
  {
    //prints out the fsize 
      if(strcmp(entry->d_name,"..")!=0 && strcmp(entry->d_name,".")!=0)
    fsize(&fileinfo);
  }
  if(strcmp(entry->d_name,"..")!=0 && strcmp(entry->d_name,".")!=0)
  printf(" \t %s \n ", entry->d_name);
  }
closedir(curdir);
return 0;
}
inline void printsize(off_t siz)
{
  printf("%ld", (long) siz); 
}
//returns the size 
void fsize(struct stat * fileinfo)
{
  printsize(fileinfo->st_size);
  return;
}


//PROGRAM TO q2 AND Q3 
