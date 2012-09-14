#include <stdio.h>
#include <unistd.h>

int main(int argc, char * argv[])
{
  if(argc==1)
    {
    printf("Too few arguments");
    return 1;
    }
  double ans=atoi(argv[argc-1],"%f",&ans);
  if (ans==0)
   {
     printf("Last argument is not a valid number");
     return 1;
   }
    ans=ans*ans*ans;
  printf("Process id of cube : %d\n", getpid());
  if(argc==2)
    {
    printf("the answer is %f",ans);
    return(0);
    }
  else
  {	
    sprintf(argv[argc-1], "%f", ans);
    if(execvp(argv[1], &argv[1])==-1)
    printf("error while trying to excep");
  }
  return 1;
}


