/*Program to inplement ls -l <file> command in c*/

#include<fcntl.h>					//required for file control(open, close, stat etc)	
#include<sys/stat.h>					//required for macros S_ISDIR, S_IRUSR etc
#include<pwd.h>						//required for definition of struct passwd
#include<time.h>					//required for time operations (struct tm, localtime(), etc)
#include<stdio.h>

char* getmonth(int);				//function to get the month name given its cardinal no.
void prnfilepermissions(unsigned int);		//function to print file permissions in user readable format rwxrwxrwx
void prnlinks(int);				//function to print number of links to a given file
void prnuid(uid_t);				//function to print file's owner's name given owner's id
void prngid(gid_t);				//function to print group member name given group id
void prnsize(off_t);				//function to print filesize in bytes given input in off_t format
void prnmodtime(time_t);				//function to print the time the file was last modified in format mon date hour:min
void prnfilename(char *);				//function to print filename


int main(int argc, char *argv[])
{
	if(argc!=2)					//reqd filename argument
	{
		printf("Format : %s <filename>\n", argv[0]);
		exit(1);
	}
	
	struct stat file;				//structure to store file information
	
	if(stat(argv[1], &file)<0)			//fn to fetch file info. returns negative value if it fails.
	{
		fprintf(stderr, "Error getting statistics for file %s\n", argv[1]);
		exit(1);
	}
	
	prnfilepermissions(file.st_mode);		//st_mode contains user permissions in integer format
	printf(" ");
	prnlinks(file.st_nlink);			
	printf(" ");
	prnuid(file.st_uid);				//st_uid contains user id (owner) in uid_t format
	printf(" ");
	prngid(file.st_gid);				//st_gid contains group id in gid_t format
	printf(" ");
	prnsize(file.st_size);				//st_gid contains file size in off_t format
	printf(" ");
	prnmodtime(file.st_mtime);			//st_mtime contains time info in time_t format
	printf(" ");
	prnfilename(argv[1]);
	printf("\n");
		
	return 0;
		
}


char* getmonth(int mno)
{
	switch(mno)
	{
		case 1 : return "Jan";
		case 2 : return "Feb";
		case 3 : return "Mar";
		case 4 : return "Apr";
		case 5 : return "May";
		case 6 : return "Jun";
		case 7 : return "Jul";
		case 8 : return "Aug";
		case 9 : return "Sep";
		case 10 : return "Oct";
		case 11 : return "Nov";
		case 12 : return "Dec";
		default : return "null";
	}
}

void prnfilepermissions(unsigned int permissions)
{
	if(S_ISDIR(permissions))				//returns true if directory, false otherwise
		printf("d");
	else 
		printf("-");
		
	printf((permissions & S_IRUSR) ? "r" : "-");		//print r if owner has read permision, otherwise -
	printf((permissions & S_IWUSR) ? "w" : "-");		//print w if owner has write permission, otherwise -
	printf((permissions & S_IXUSR) ? "x" : "-");		//print x if owner has execute permission, otherwise -
	printf((permissions & S_IRGRP) ? "r" : "-");
	printf((permissions & S_IWGRP) ? "w" : "-");
	printf((permissions & S_IXGRP) ? "x" : "-");
	printf((permissions & S_IROTH) ? "r" : "-");
	printf((permissions & S_IWOTH) ? "w" : "-");
	printf((permissions & S_IXOTH) ? "x" : "-");
	
	return;
}

void prnlinks(int n)
{
	printf("%d", n);
	return;
}

void prnuid(uid_t uid)
{
	struct passwd user;					//struct passwd contains username amongst other info
	user=*getpwuid(uid);					//struct * passwd = getpwuid(uid_t)
	
	printf("%s", user.pw_name);
	return;
}

void prngid(gid_t gid)
{
	struct passwd group;
	
	group=*getpwuid(gid);
	
	printf("%s", group.pw_name);
	return;
}

void prnsize(off_t size)
{
	printf("%ld", (long) size);				//type cast off_t to long int
	return;
}


void prnmodtime(time_t t)
{
	struct tm time;
	
	time=*localtime(&t);					//convert time_t format to tm format -- struct * tm = localtime(&time_t)
	
	printf("%s %d ", getmonth(time.tm_mon), time.tm_mday);
	
	if((time.tm_hour/10)==0)				//print leading '0' if less than 10
		printf("0");
		
	printf("%d:", time.tm_hour);
	
	if((time.tm_min/10)==0)
		printf("0");
		
	printf("%d ", time.tm_min);
	
	return;
}

void prnfilename(char * filename)
{
	printf("%s", filename);
	return;
}
