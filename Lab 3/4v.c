#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/utsname.h>

void main()
{
	struct utsname data;
	uname(&data);
	write(1,"OS Name: ",9);
	write(1,(void *)&(data.sysname),sizeof(data.sysname));
	write(1,"\nNode Name: ",12);
	write(1,(void *)&(data.nodename),sizeof(data.nodename));

	write(1,"\nOS Release: ",13);
	write(1,(void *)&(data.release),sizeof(data.release));

	write(1,"\nOS Version: ",13);
	write(1,(void *)&(data.version),sizeof(data.version));

	write(1,"\nHardware Identifier: ",22);
	write(1,(void *)&(data.machine),sizeof(data.machine));

	write(1,"\n",1);
}
