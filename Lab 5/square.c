#include <stdio.h>
#include <unistd.h>

int main(int argc, char * argv[])
{
	printf("a");
	execl( argv, argv, (char *)0);
}

