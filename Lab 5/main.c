#include <stdio.h>
#include <unistd.h>

int main(int argc,char * argv[])
{
	
	/*int ans=atoi(argv[noarg]);
	printf("%d\n",ans);
	ans++;
	printf("%d",ans);
	 int noarg=argc-1;
	*/

  	 execl( argv, (char *)0);
	
	return(0);
}
