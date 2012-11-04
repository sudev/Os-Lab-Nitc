#include <pthread.h>
//for thread library 
#include <stdlib.h>
#include <semaphore.h>
//semaphore.h is Posix standard 
//sys/sem.h is of system V standard 
#include <stdio.h>

#define exact_num 100000000

typedef int buffer_type;
//will be using this 
#define size 5
//mutex lock for threads  producer and consumer
pthread_mutex_t mutex;
//variable for semaphores 
sem_t full, empty;
//initialising the buffer 
buffer_type buffer[size];
//counter used in buffer 
int counter;
//variable to carry thread id 
pthread_t thread_id; 
//passing the atributes into thread
pthread_attr_t attr; 

void *producer_thread(void *param);
void *consumer_thread(void *param);

void initializi() {
   pthread_mutex_init(&mutex, NULL);
   //intialising the semaphore full and value = 0 
   sem_init(&full, 0, 0);
   //initailising the semaphore empty to the valuee of buffer size 
   sem_init(&empty, 0, size);
   //initailising threads 
   pthread_attr_init(&attr);
   //counting the buffer 
   counter = 0;
}

void *producer_thread(void *param) {
   buffer_type item;

   while(1) {
      /* sleep for a random period of time */
      int rNum = rand() / exact_num;
//	printf("%d",rNum);
      sleep(rNum);
//create a random number 
      item = rand();
//wait till mutex says hi 
      sem_wait(&empty);
//lock using mutex
      pthread_mutex_lock(&mutex);
//insert a value using the generated random number 
      if(produce_item(item)) {
         fprintf(stderr, " Producer report error condition\n");
      }
      else {
         printf("Producer working %d\n", item);
      }
//realease the mutex lock
      pthread_mutex_unlock(&mutex);
//doubt ---------------------------------------------------
      sem_post(&full);
   }
}

void *consumer_thread(void *param) {
   buffer_type item;

   while(1) {
      //sleep for random time
      int rNum = rand() / exact_num;
      sleep(rNum);
//acquire full lock should not be completely empty 
      sem_wait(&full);
//lock using mutex
      pthread_mutex_lock(&mutex);
      if(consume_item(&item)) {
         fprintf(stderr, "Consumer report error condition\n");
      }
      else {
         printf("Consumer working  %d\n", item);
      }
//unlocki the mutex 
      pthread_mutex_unlock(&mutex);
//post empty
      sem_post(&empty);
   }
}

//produce item 
int produce_item(buffer_type item) {
   /* When the buffer is not full add the item
      and increment the counter*/
   //for particular producer the counter should be less than the buffer size 
   if(counter < size) {
      buffer[counter] = item;
      counter++;
      return 0;
   }
   else { 
     return -1;
   }
}

//consume and removing an item form the buffer 
int consume_item(buffer_type *item) {
//check if the buffer is not full
   if(counter > 0) {
      *item = buffer[(counter-1)];
      counter--;
      return 0;
   }
   else { 
   //return empty if the producer hasnt produced anything 
      return -1;
   }
}

int main(int argc, char *argv[]) {
     if(argc != 4) {
      fprintf(stderr, "./a.out <total sleep time> <no of produce thread> <no of consumer threads>");
   }
   int totalsleep = atoi(argv[1]),nConsumer = atoi(argv[3]),nProducer = atoi(argv[2]);
   //main thread running time ,consumer thread , producer thread values assigned  
   //number of consumer thread
   //number of producer threads
   //now initailising threads ans semaphore values 
   initializi();
   //creating the required number of producer and consumer threads
   int i;
  
   for(i = 0; i < nConsumer; i++) {
      pthread_create(&thread_id,&attr,consumer_thread,NULL);
       //printf("%d\t%d\n",i,&thread_id);
   }
    for( i = 0; i < nProducer; i++) {
      pthread_create(&thread_id,&attr,producer_thread,NULL);
      //printf("%d\t%d\n",i,&thread_id);
    }
   //make this a small value for earlier terminatiuon 
   sleep(totalsleep);
   printf("finished sleep time of main \t%d\t seconds  \n",totalsleep);
   exit(0);
}

