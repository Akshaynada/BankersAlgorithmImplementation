//Title: Banker's Algorithm using mutex locks and multithreading using pthreads
//To be submitted to: Professor Manimala
//Author: Akshay Shetty,Asif,Parashivmurthy and Sriharsha B.T
//Class: 5th CS 'A'

//Note: Navigation:
//Runner function - ESC followed by /runnerfn
//Main funtion    - ESC followed by /mainfn

//Program compilation: gcc bankersos.c -lpthread

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<stdbool.h>
#include<unistd.h>


//Creating a mutex lock
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;


//Process information

struct Process
{

	int pid      ;		//Proccess id
	int completed;		//0-->Not completed 1--->Completed
	int MxAl[100];		// Maximum claim of the process 
	int CrAl[100];		//Currently allocated resources
	int Req[100] ;		//Resource Request
	int Need[100];		//Calculated as <Need>=<MxAl>-<CuAl>
};




struct Process tnPro[100];	//Shared
struct Process nPro[100];	//Shared
static int Available[100]; 	//Shared

int nR,nP;
int *MI;





// The comparison of <Req> <= <Need> ,<Req> <= <Available>  and <Need> <= <Available>   
bool compare1(int a[],int b[])
{

	int i,j;

	for(i=0;i<nR;i++)
		{	

			if(a[i]>b[i]) return false;

		}

	return true;

}



//Copy the contents of the resource allocations so as to have the copyings ACTUAL-->TEMPORARY 


void copyAvailable(int a[],int b[])
{
int i;

for(i=0;i<nR;i++)
{
b[i]=a[i];
}

}


//Copy the process information before actual allocation is possible

void copyProcess(struct Process a[],struct Process b[])
{

int i,j;


for(i=0;i<nP;i++)
{
        
                
                        b[i].pid=a[i].pid;
                        b[i].completed=a[i].completed;
                        copyAvailable(a[i].MxAl,b[i].MxAl);
                        copyAvailable(a[i].CrAl,b[i].CrAl);
                        copyAvailable(a[i].Need,b[i].Need);
                        copyAvailable(a[i].Req,b[i].Req);
                
}


}



//Display the Current Allocation , Maximum Allocation and Need
void show(int a[])

{

int i=0;

printf("\t\t< ");
for(i=0;i<nR;i++)
{

printf("%d ",a[i]);

}

printf(">");

}





//Display the process allocation table

void show_allocation()
{

int i,j;





printf("\n\n ________________________________________________________________________________");
printf("\n\n Process\t\tAllocated\t\tMaximum\t\t\tNeed");
printf("\n\n ________________________________________________________________________________");

for(i=0;i<nP;i++)
{

printf("\n\n %d",nPro[i].pid);
printf("\t");
show(nPro[i].CrAl);
show(nPro[i].MxAl);
show(nPro[i].Need);

}
printf("\n\n ________________________________________________________________________________");

printf("\n\nAVAILABLE:");
show(Available);
printf("\n\n");




}





void safety_algo()
{
int i,j,k=0;
int pcount=0;	 		//Count the no of processes executed in the current state
int change_after_iteration=1;	//Check for the system deadlock as no process executes
int tAvailable[100];		//Temporary available
int pseq[20];			//Process sequence

copyAvailable(Available,tAvailable);
copyProcess(nPro,tnPro);

			while(pcount<nP && change_after_iteration>0)
				{
 					change_after_iteration=0;

					for(i=0;i<nP;i++)

					{	


						if(compare1(tnPro[i].Need,tAvailable) && tnPro[i].completed==0)
						{

						pseq[k]=tnPro[i].pid;
						k++;
						pcount++;
						tnPro[i].completed=1;		
              				        change_after_iteration++;
   
						for(j=0;j<nR;j++)
						{
						 tAvailable[j]=tAvailable[j]+tnPro[i].CrAl[j];
						 tnPro[i].Need[j]=0;
 						 tnPro[i].CrAl[j]=0;
						}



						}


					}

      }

if(pcount==nP)
{
printf("\nThe system is in safe state");
printf("\n\nThe safe state is < ");

for(k=0;k<nP;k++)
printf("P%d ",pseq[k]);
printf(">");
}

else
{
printf("\nThe system is not in safe state!!");
sleep(2);
exit(0);
}


}



//runnerfn

//Bankers algorithm is applied to each thread of process request


void *runner(void *pid)
{




int *p=pid;
int P_id=*p;		// Get the required proceess id


pthread_mutex_lock(&mutex1);




int i,j,k;
int tAvailable[100];		//Temporary available array to pretend allocaton
int pcount=0;			//Counting the number of processes which can execute under the allocation
int change_after_iteration=1;	//Counting the processes which execute in each iteration . change_after_iteration=0----> System has reached deadlock state 

int pseq[20];


//Temporary storage of the Available resources and the process allocations

copyAvailable(Available,tAvailable);
copyProcess(nPro,tnPro);




printf("\n\nThread created for process %d",nPro[P_id].pid);

printf("\n\nEnter the request of the resources by the process %d: ",nPro[P_id].pid);


//Accept the resource request input

for(i=0;i<nR;i++)
{

	scanf("%d",&nPro[P_id].Req[i]);
	tnPro[P_id].Req[i]=nPro[P_id].Req[i];
}


	
		if(compare1(tnPro[P_id].Req,tnPro[P_id].Need) &&  compare1(tnPro[P_id].Req,tAvailable)) // <Req> <= <Need> and <Req> <= <Available>

		{


			





//<CrAl> = <CrAl> + <Req> 
//<Need> = <Need> - <Req>
//<Available> = <Available> - <Req>


			for(i=0;i<nR;i++)
				{
				   tnPro[P_id].CrAl[j] = tnPro[P_id].CrAl[j]+tnPro[P_id].Req[j];
				   tnPro[P_id].Need[j]=tnPro[P_id].Need[j]-tnPro[P_id].Req[j];
				   tAvailable[j]=tAvailable[j]-tnPro[P_id].Req[j];
				}




k=0;
 pcount=0;	 		//Count the no of processes executed if the request is accepted
 change_after_iteration=1;	//Check for the system deadlock as no process executes


			while(pcount<nP && change_after_iteration>0)
				{
 					change_after_iteration=0;

					for(i=0;i<nP;i++)

					{	


						if(compare1(tnPro[i].Need,tAvailable) && tnPro[i].completed==0)
						{

						pseq[k]=tnPro[i].pid;
						k++;
						pcount++;
						tnPro[i].completed=1;		
              				        change_after_iteration++;
   
						for(j=0;j<nR;j++)
						{
						 tAvailable[j]=tAvailable[j]+tnPro[i].CrAl[j];
						 tnPro[i].Need[j]=0;
 						 tnPro[i].CrAl[j]=0;
						}



						}


					}

				}		

		}
	





if(pcount==nP)		//All the processes execute and hence the request is accepted
	{

 		printf("\n\nThe system is in safe state and the request of process %d is accepted \n",tnPro[P_id].pid);
 

//Print the safe sequence

		printf("\nThe safe sequence is < ");
		for(k=0;k<nP;k++)
		printf("P%d ",pseq[k]);
		printf(">");

//Accept the request and do the allocations

		for(j=0;j<nR;j++)
			{
        			nPro[P_id].CrAl[j] = nPro[P_id].CrAl[j]+nPro[P_id].Req[j];
        			nPro[P_id].Need[j]=nPro[P_id].Need[j]-nPro[P_id].Req[j];
        			Available[j]=Available[j]-nPro[P_id].Req[j];
			}	



		show_allocation();	



	}

else
	{

		printf("\n\tThe system is in unsafe state and hence the request is not accepted");

	}



printf("\n\tEnd of thread for process %d \n",tnPro[P_id].pid);




pthread_mutex_unlock(&mutex1);		//Unlock the mutex so that other threads can continue
pthread_exit(0);

}





//mainfn


int main(int argc,char *argv[])
{

	int i,j;
	


	system("clear");


	printf("Enter the number of resources: ");
        scanf("%d",&nR);

//Enter the maximum instances of each resource 


	printf("\nEnter the max instances of each resources :\n");
	MI=(int *)malloc(nR*sizeof(int));
	for(i=0;i<nR;i++)
		{
			printf("\nRequest [%d]  :",i+1);
			scanf("%d",&MI[i]);
		}

//Display the max instance of each resource


	for(i=0;i<nR;i++)
		{
			  printf("\nResource[%d]= %d",i,MI[i]);
		}


//Enter the number of processes in the system

	printf("\nEnter the number of processes: ");
	scanf("%d",&nP);

        
     	
	



	printf("\nEnter the claim for each process:");	//Enter the maximum resources required by each process MxAl[Process][Resource]
	for(i=0;i<nP;i++)
		  {
			printf("\nFor process %d",i+1);
			
			for(j=0;j<nR;j++)
				{
					printf("\nEnter for resource %d : ",j+1);
					scanf("%d",&nPro[i].MxAl[j]);
				}
	  	}
		 


	printf("\nEnter the allocation for each process:\n"); 	//Enter the allocation that has been already been done to each process CrAl[Process][REs]
	for(i=0;i<nP;i++)
		{
	
			printf("\nFor process %d : ",i+1);
			for(j=0;j<nR;j++)
				{
					while(1)
					{
					printf("\nEnter for resource %d : ",j+1);
					scanf("%d",&nPro[i].CrAl[j]);
					if(nPro[i].CrAl[j]<=nPro[i].MxAl[j]) break;
					else
					printf("\nSorry CrAl <= MxAl");
					}
				}
		}


//Need for each process is calculated 



	for(i=0;i<nP;i++)
		{

 	
			for(j=0;j<nR;j++)
				{
					nPro[i].Need[j]=nPro[i].MxAl[j]-nPro[i].CrAl[j];
				}
}


//Assigning the process id and completed=false


for(i=0;i<nP;i++)
{
nPro[i].pid=i+1;		//Process id
nPro[i].completed=0;		//NO process has completed its request of resources
}


	
//Calculate the Avaialble resoures in the system that can be used for allocation

	for(i=0;i<nR;i++)
	{
            int total=0;
	    Available[i]=0;
	    for(j=0;j<nP;j++)
		{
			total+=nPro[j].CrAl[i];
		}
		
	Available[i]=MI[i]-total;
	}

pthread_mutex_lock(&mutex1);
safety_algo();
pthread_mutex_unlock(&mutex1);
            
show_allocation();	//Show the process allocation table 



pthread_t tid[100];	//pthread for multithreading

	

//Create a thread for each process request and run the banker's algorithm

	for(i=0;i<nP;i++)
		{
			pthread_create(&tid[i],NULL,runner,&i);
			sleep(1);
		}


          for(j=0;j<nP;j++)
		{
	
			pthread_join(tid[j],NULL);

		}


//The main() has to wait for all the threads to finish execution


pthread_mutex_destroy(&mutex1);
return 0;


}

// End of the program




