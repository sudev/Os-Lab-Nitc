#include "mypc.h"

void consumer();

int main()
{
	consumer();
}

void consumer()
{
	int n=0, j;
	share *mem=memory();
	
	while(1)
	{
		sem_wait(&mem->full);
		sem_wait(&mem->mutex);
		
		printf("Consumer consumed %d\n", (mem->buffer[n++]));
		n%=BUFFER_SIZE;
		sem_post(&mem->mutex);
		sem_post(&mem->empty);
		
		for(j=0;j<cdelay;j++);
	}
}


