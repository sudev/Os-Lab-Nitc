#include<sys/ipc.h>
#include<sys/shm.h>
#include<stdio.h>
#include<semaphore.h>
#include<errno.h>
#include<sys/types.h>



#define BUFFER_SIZE 10
#define KEY 124
#define pdelay 200000000
#define cdelay 100000000

typedef struct share
{
	int buffer[BUFFER_SIZE], i;
	sem_t mutex, full, empty;
}share;

share * memory()
{

	key_t key=KEY;
	int shmid = shmget(key , sizeof(share), IPC_CREAT | 0666);
	
	if(shmid>0)
		return shmat(shmid, NULL, 0);
	
	return NULL;
}

void init()
{
	int temp;
	share *mem=memory();
	
		sem_init(&mem->mutex,1,1);
    		sem_init(&mem->empty,1,BUFFER_SIZE);
    		sem_init(&mem->full,1,0);
    	
    
    	
}
	
		
