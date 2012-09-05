/*Program to print OS version details and processor name using uname() system call.*/

#include<sys/utsname.h>					//contains definition of struct utsname.
#include<stdio.h>

int main()
{
	struct utsname OSinfo;
	
	if((uname(&OSinfo))==-1)			//uname() returns -1 on error.
	{
		fprintf(stderr, "Error getting system info.\n");
		exit(1);
	}
	
	printf("Your OS is 		: %s\n", OSinfo.sysname);
	printf("Your release is 	: %s\n", OSinfo.release);
	printf("Your version number is 	: %s\n", OSinfo.version);
	printf("Your machine is 	: %s\n", OSinfo.machine);
	
	return 0;
}
