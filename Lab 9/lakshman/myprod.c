#include "mypc.h"
#include<pthread.h>

void producer();

int main()
{
	init();
	producer();
}

void producer()
{
	int n=0, j;
	share *mem=memory();
	while(1)
	{	
		sem_wait(&mem->empty);
		sem_wait(&mem->mutex);
		
		(mem->buffer)[n++]=mem->i;
		n%=BUFFER_SIZE;
		printf("Producer placed item %d\n", mem->i);
		(mem->i)++;
		
		sem_post(&mem->mutex);
		sem_post(&mem->full);
		for(j=0;j<pdelay;j++);
		
	}
}

