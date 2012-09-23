#include <iostream>
#include <fstream>
#include <string>

using namespace std;
//universal array containing all the info 
int array[10][10]={{},{}};
//PCB for process 
int iowait=0;
int * readyqueue();
int over();
void readandsave();
void ioqueuer(int *,int *);
int ptime=0,noofprocess;
//keeps track of the current process 

int current=0;
int printarray[1000];
struct process
{
	int cpu[10];
	int io[10];
	int arival;
	int numcpu;
	int numio;
	int signal[3];
	int currentcpu;
	int currentio;
	//the status array is used to get the status of any process which 
	//like working cpu 1st bit = 1 , io 2nd bit = 1; finished 3rd bit = 1  
};
//all values are intialized to zero using new constructor 
struct process *proc = new struct process[10];

void readandsave(){

string line;
int count,i,nop=0,just,nopt;
ifstream myfile0 ("test");
while (!myfile0.eof())
    {
		getline (myfile0,line);
		nop++;
	}
nop--;
nopt=nop;
noofprocess=nop;
cout<<"Total no fo process  "<<nop<<endl;
int countarray[nop];
ifstream myfile ("test");
int cou=0;
while (nop)
    {
	getline (myfile,line);
	count=i=0;
	while(line[i]!='\0')
		{
			if(line[i]==' ')
			count++;
			i++;

		}
	countarray[cou]=count+1;
	nop--;
	cou++; 
    }
ifstream myfile2 ("test");
for(int x=0;x<nopt;x++)
	{
	for(int z=0;z<countarray[x];z++ )
		{ 
		myfile2>>just;
		array[x][z]=just;
		}
	}
for(int a=0;a<nopt;a++)
	{
	int t=1;
	for(int b=0;b<countarray[a];b++ )
		{ 
		cout<<array[a][b]<<" ";\
		//taking values into arival array 
		if(b==1)
		proc[a].arival = array[a][b];
		//taking values into job queue and i/o queue				
		if( b > 1)
		{ 
			if(t)
			{
			proc[a].cpu[proc[a].numcpu]=array[a][b];
			proc[a].numcpu++;
			t=0;		
			}
			else
			{				
			proc[a].io[proc[a].numio]=array[a][b];
			proc[a].numio++;	
			t=1;
			}				
		}				
		}
		//testing results using sample outputs 
		cout<<endl;
		cout<<"arrival time  "<<proc[a].arival<<endl; 
		cout<<"Cpu Bursts";
		for(int i=0;i<proc[a].numcpu;i++)
		cout<<"\t"<<proc[a].cpu[i]<<"\t";
		cout<<endl<<"number of cpu process "<<proc[a].numcpu<<endl;
		cout<<"IO Bursts";
		for(int i=0;i<proc[a].numio;i++)
		cout<<"\t"<<proc[a].io[i]<<"\t";
		cout<<endl<<"number of io process "<<proc[a].numio<<endl;
		cout<<endl<<"-------------------------------------------"<<endl;
}

}



int main () 
{
	readandsave();
	//we have all the details of the process t 	he process structure now we have to 
	//manipulate the data using suitable methods 
//time 
//print point 
int pp=0;

//select the process with least cpu burst 
while(over())
	{	
	int * tem = readyqueue();
	//cout<<endl<<"process to be executed is "<<*tem;
	//now to take record of all the happenings
	/* trying to keep print the whole stuff */
	cout << "the process executed at time\t " <<ptime<<"\twas\t"<<current+1<<endl;
	/*if(ptime==0)
	{ 
		printarray[pp] = current;
		printarray[pp+1] = 1;
	}
	else
	{
		if(printarray[pp - 1] == current )
			{
			printarray[pp]++;
			}
		else
			{
			pp++;
			printarray[pp] = current;
			pp++;
			printarray[pp] = 1;
			}
	}
	for(int i; i < pp+1;i=i+2)
		cout<<printarray[i]<<" : "<<printarray[i+1]<<"\t";
	*/
	(*tem)--;
	ptime++;
	
	}
}



//function to check completion of all the process 
int over()
{
	for(int i =0 ; i < noofprocess; i++)
	{
		if(proc[i].signal[1] != -1)
		{
		return 1;
		}
	}
	return 0;
}
int * readyqueue()
{
	//to find the minimum 
	int * temp = NULL;
	for(int i=0;i<noofprocess;i++)
	{
	//checking for the completion of the process 
	if(proc[i].cpu[proc[i].currentcpu] <=0)
		{
		if(proc[i].numcpu>proc[i].currentcpu )
			proc[i].currentcpu++;
			//calling io opertion to complete
			ioqueuer(&proc[i].arival, &proc[i].currentio);
		}
	//set the process completion signal 
	if(proc[i].numcpu < proc[i].currentcpu )
		proc[i].signal[1]=-1;
	//now add the same to jobqueue considering arrival time and signal 
	if(proc[i].arival<=ptime && proc[i].signal[1]==0)
		{
		//this gives out a pointer to minimum process
		if(temp == NULL)
			{
			temp = &proc[i].cpu[proc[i].currentcpu];
			current = i;
			}
		else 	
			{
			if(*temp > proc[i].cpu[proc[i].currentcpu])
			temp = &proc[i].cpu[proc[i].currentcpu];
			current = i;
			}
		}
	}
	return temp;
}
void ioqueuer(int *a,int *b)
{
	*a = *a + ptime + iowait;
	iowait = *a + iowait;
	*b = *b + 1;
}
