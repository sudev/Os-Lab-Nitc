/*Write two versions of a shortest-next-CPU-burst-first process scheduler algorithm, one pre-emptive
and another non-pre-emptive. The algorithm always dispatches the job that has the shortest next
CPU burst among the jobs that are in contention.
Input:
(i) A file in which a number of processes and their CPU bursts and I/O bursts are listed in
milliseconds.
Eg:
1 0 100 30 80 75 35 70 3 (job number, arrival time, CPU burst, I/O burst, CPU burst, I/O burst..)
2 5 20 45 4 41 34 5
3 10 15 13 12 18 100
(ii) Whether to use pre-emptive algorithm or non-pre-emptive.
Assume that (i) There is a single I/O queue and a single I/O device, and FCFS algorithm (which is
non-pre-emptive by definition) is used on the I/O queue. i.e, if there are two processes waiting on
I/O queue, the one that reached the queue first will get access to the I/O device.
(ii) Context switch time is negligible.
Output: The processes executed on CPU, along with the time duration.
Eg: 1: 20 2:80 3:25 1:30 2:20 ... (either in a file r on standard output).
*/

#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>
#include<string.h>

struct jobs
{
	int jno;
	int atime;
	int burst[10];
	int cur;				//The current burst position the job is at
};
struct jobs * job[100]={NULL};
struct jobs * Pri_Q[100]={NULL};
struct jobs * active=NULL;		//stores the address of the process currently being executed by the CPU




struct node
{
struct jobs *ptr;
struct node *next;
};
struct node *IOhead, *IOtail;		//for I/O queue


void Pri_Q_insert(struct jobs * job);
struct jobs * Pri_Q_remove();


void IOenqueue(struct jobs *);
struct jobs * IOdequeue();


void getinput();
void checkjobs();
void IOdec();
void CPUdec();
void maxheapify(int pos);


_Bool queue_empty(struct node * head);


int Pri_Q_size=0, no_jobs=0;
int processtime;
int choice;			//preemptive or non-preemptive
int time=-1;
	
	
int main()
{
	
	int i;
	
	struct jobs * discard;
	
	getinput();
	
	printf("\nWhich Scheduling scheme do you want to use?\n\n1.Preemptive\n2.Non-Preemptive\n\nEnter your choice : ");
	scanf("%d", &choice);
	printf("\n");
	if(choice!=1 && choice !=2)
	{
		printf("invalid choice! Exiting...\n");
		return 1;
	}
	while(Pri_Q_size==0)			//simply loop until any process enters ready queue
	{
		++time;
		checkjobs();
		
		
	}
	
			
	while(active!=NULL || !queue_empty(IOhead)||Pri_Q_size>0)		//enter if some process exists either in CPU(active)
										// or in ready queue or in I/Oqueue
	{
		
		IOdec();					//decrement IO burst
		
		if(active==NULL)
		{
			active=Pri_Q_remove();		//if no process is active, then insert the topmost process
							//in the ready queue into the CPU and reset the process time counter.
			processtime=0;
		}
				
		CPUdec();				//decrement CPU burst of active process
			
		++time;
		
		checkjobs();				//check for newly arrived jobs
	}
	printf("\n\n");	
	return 0;
}


void getinput()			/*read input letter by letter. if EOF is found, then quit. if new line character is found,
					then start a new job. if a space occurs, then add new burst time for the current job.
					for whatever reason, a newline input is read at the end of all input even if it doesnt
					exist in the file. so decrement the no of jobs by 1 in the end.*/
{
	int i=-1,j=0, k=0;
	char c[4];
	FILE *fp;
	fp=fopen("input.txt", "r");
	
	while(c[k]!=EOF)
	{	no_jobs++;
		job[++i]=malloc(sizeof(struct jobs));
		fscanf(fp, "%d", &(job[i]->jno));
		fscanf(fp, "%d", &(job[i]->atime));
		job[i]->cur=0;
		j=0; 
		k=0;
		c[k]=getc(fp);				//read space after atime
		while(c[k]=getc(fp))
		{
			if(c[k]==EOF)
				break;
			if(c[k]=='\n')
			{
				job[i]->burst[j++]=atoi(c);
				
				break;
			}
			if(c[k]==' ')
			{
				job[i]->burst[j++]=atoi(c);
				k=0;
					
			}
			
			else ++k;
			
			
		}					
					    
	}
	
	free(job[i]);
	job[i]=NULL;
	no_jobs--;
	fclose(fp);
	
	return;

}


_Bool queue_empty(struct node * head)
{
	if(head==NULL)
		return 1;
	else
		return 0;
}

void IOenqueue(struct jobs * job)
{
	struct node * ptr;
	ptr=malloc(sizeof(struct node));
	ptr->ptr=job;
	ptr->next=NULL;
	
	if(queue_empty(IOhead))
	{
		IOhead=ptr;
		IOtail=ptr;
	}
	else
	{
		IOtail->next=ptr;
		IOtail=ptr;
	}
}

struct jobs * IOdequeue()
{
	struct jobs * ptr;
	ptr=IOhead->ptr;
	if(IOhead==IOtail)
		IOhead=IOtail=NULL;
	else
		IOhead=IOhead->next;
		
		return ptr;
}


void Pri_Q_insert(struct jobs * job)
{
	Pri_Q_size+=1;
	Pri_Q[Pri_Q_size]=job;
	int pos=Pri_Q_size;
	struct jobs * temp;
	while((pos>1) && (Pri_Q[pos]->burst[Pri_Q[pos]->cur]<Pri_Q[pos/2]->burst[Pri_Q[pos/2]->cur]))
	{
		temp=Pri_Q[pos];
		Pri_Q[pos]=Pri_Q[pos/2];
		Pri_Q[pos/2]=temp;
	}

}

struct jobs * Pri_Q_remove()
{
	struct jobs * temp=Pri_Q[1];
	Pri_Q[1]=Pri_Q[Pri_Q_size];
	Pri_Q[Pri_Q_size]=NULL;	
	if(Pri_Q_size>0)
		Pri_Q_size--;
	maxheapify(1);
	return temp;
}


void maxheapify(int pos)
{
	int l=2*pos;
	int r=l+1;
	struct jobs * temp;
	int least;
	
	if((l<=Pri_Q_size) && (Pri_Q[l]->burst[Pri_Q[l]->cur]<Pri_Q[pos]->burst[Pri_Q[pos]->cur]))
		least=l;
	else 	least=pos;
	
	if((r<=Pri_Q_size) && (Pri_Q[r]->burst[Pri_Q[r]->cur]<Pri_Q[least]->burst[Pri_Q[least]->cur]))
		least=r;
		
	if(least!=pos)
	{
		temp=Pri_Q[pos];
		Pri_Q[pos]=Pri_Q[least];
		Pri_Q[least]=temp;
		maxheapify(least);
	}
}

	
void checkjobs()			//if any job's arrival is equal to the current time, insert it into the ready queue
{
	int i=0;
	for(i=0;i<no_jobs;++i)
		if(time==job[i]->atime)
		{
			Pri_Q_insert(job[i]);
			if(active!=NULL && choice==1)
				if(active->burst[active->cur]>Pri_Q[1]->burst[Pri_Q[1]->cur])
				{	
					printf("%d:%d\t", active->jno, processtime);
					Pri_Q_insert(active);
					active=NULL;
				}
					
			
		}
}

void IOdec()			//if queue is not empty, decrement IO burst and if it reaches 0 check if next io burst is non zero.
				//if so, add process to ready queue. if preemptive, interrupt current process.
{	
	struct jobs * discard;

	if(!queue_empty(IOhead))
	{
		if(--(IOhead->ptr->burst[IOhead->ptr->cur])<=0)
			if((IOhead->ptr->burst[++(IOhead->ptr->cur)])>0)
			{
				Pri_Q_insert(IOdequeue());
				if(active!=NULL && choice==1)
				if(active->burst[active->cur]>Pri_Q[1]->burst[Pri_Q[1]->cur])
				{	
					printf("%d:%d\t", active->jno, processtime);
					Pri_Q_insert(active);
					active=NULL;
				}
				
				
			}
			else
				discard=IOdequeue();
	}
}

void CPUdec()			//decrement cpu burst time of current process. if it reaches 0, and next burst value
				//is non-zero, queue process in IOqueue.
{	if(active==NULL)	//nothing to be done if there is no active process
		return;
	++processtime;
	if(--(active->burst[active->cur])<=0)
	{
		struct jobs * discard;
		
		printf("%d:%d\t", active->jno, processtime);
		if(active->burst[++(active->cur)]>0)
			IOenqueue(active);
		
		active=NULL;
			
	}
}

