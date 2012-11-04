#include <stdio.h>
#include <pthread.h>

int sum;
void *runner(void *param);

int main(int argc, char *argv[])
{
//creating the thread id
	pthread_t tid;
//creating the attribute 
//this case the attributes are the default attributes and its solves the problem//here 
	pthread_attr_t attr;
//initialise the pthread with the atrributes 
	pthread_attr_init(&attr);
//creating the thread with the attributes id the program to be run , and the argumnet to be given for the runner 
	pthread_create(&tid,&attr,runner,argv[1]);
	pthread_join(tid,NULL);
	printf("Sum %d\n",sum);
}
void *runner(void *a)
{
	int i,k=atoi(a);
	sum = 0;
	for(i = 1; i<=k;i++)
		sum+=i;
	pthread_exit(0);
}

