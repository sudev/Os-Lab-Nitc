#include <stdio.h>
#include <fctnl.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>

void fsize(struct stat *);
inline void printsiz(off_t);

int main(int arg,char * argv[])
{
  if (arg != 2)
  {
    printf(" Please check this format :: %s file/foldername",argv[0]);
    exit(1);
  }
  //using dirent we use DIR , funtions 
  int ch=o,flg=0;
  printf("/n1.Question 2/n2.Question 3/n");
  if(ch ==1)
  {
    flg=1;
  }
  
  DIR *curdir;
  strucu dirent *entry;
  //fname and stat to store deatails of files 
  char *fname;
  fname = argv[1];
  struct stat fname;
  
  //existence check -1 is error
  if((stat, &fname)==-1)
  {
    perror("stat");
    exit(1)
  }
  //check for directory 
  if (!S_ISDIR(fileinfo.st_mode))
  {
    if(flg==1)
    {
    fsiz(&fileinfo);
    }
    exit(0);
  }
  //open directory 
  curdir=opendir(fname);
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
    fsize(&fileinfo);
  }
  printf(" \t %s \n ", entry->d_name);
  }
closedir(dir);
return 0;
}
inline void printsiz(off_t siz)
{
  printf("%ld", (long) size); 
}
//returns the size 
void fsize(struct stat * fileinfo)
{
  printsiz(fileinfo->st_size);
  return;
}


//PROGRAM TO q2 AND Q3 
