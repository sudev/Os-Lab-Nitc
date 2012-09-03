#include<fcntl.h>
#include<stdio.h>
#include<unistd.h>
int main(int argc, char *argv[])
{
	if(argc < 3)
	{
		write(1,"Agruments required\n",19);
		return 0;
	}
	int s,d,n;
	char buff[128];
	s=open(argv[1],O_RDONLY);
	if(s<0)
	{
		perror("Source file ");
		return 0;
	}
	d=open(argv[2],O_WRONLY |O_APPEND | O_CREAT | O_EXCL, 0644);
	if(d<0)
	{
		perror("Destination file ");
		return 0;
	}
	while((n=read(s,buff,128)) > 0)
	{
		write(d,buff,n);
	}
	close(s);
	close(d);
	write(1,"Copy Completed\n",15);
	return 0;
}
