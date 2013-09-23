/**
shmget() shared memory get used to get a shared memory space
shmat() shared memory attach
shmdt detach shared memeory 
**/ 

#include <stdio.h>
#include <sys/stat.h>
#include <sys/shm.h>

int main() { 
	
	//segment id
	int seg_id; 
	
	//pointer to shared memory segement  
	char* shared_memory;
	
	//size
	const int size = 4096;
	
	//allocate a shared memory segemnt 
	seg_id = shmget( IPC_PRIVATE, size ,S_IRUSR | S_IWUSR);
	/**
	Param one : Identifies the key of the shared memory 
	IPC_PRIVATE => A new segment is created 
	
	Param 2 :size of the require segement 
	
	Param 3 : Mode read/ write 
	S_IRUSR | S_IWUSR  => the owner can read or write things 
	**/
	
	//attaching the shared memory segement
	
	shared_memory = (char *)shmat(seg_id, NULL, 0);
	/**
	param one : id for which the segment has to be attached
	param two : the place where the shared memory has to be alloted
							if NULL is passed the operating system allocated memory @ users behalf
	param three : flag, 0 indicating that both read and write for owner 
	**/
	
	sprintf(shared_memory, "Hello mofos");
	printf("%s\n",shared_memory);
	shmdt(shared_memory);
	shmctl(seg_id, IPC_RMID, NULL);
	return 0;
	}
	
								
	
	 
	
	
	
 
