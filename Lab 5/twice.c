#include <stdio.h>
#include <unistd.h>

int main(int argc, char * argv[])
{
  if(argc==1)
    {
    printf("Too few arguments ");
    exit(1);
    }
  int ans=atoi(argv[argc-1]);
  if (ans==0)
  {
    printf("Last argument is not a valid number");
    exit(1);
  }
    ans=ans*2;
  printf("Process id of half : %d\n", getpid());
  if(argc==2)
    printf("the answer is %d",ans);
  else
  {	
    sprintf(argv[argc-1], "%d", ans);
    if(execvp(argv[1], &argv[1])==-1)
    printf("error while trying to excep");
  }
  return 1;
}
