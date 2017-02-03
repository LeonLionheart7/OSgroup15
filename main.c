#include <stdio.h>

typedef struct process
{
    int id;
    int arrivalTime;
    int burstTime;
    char name[10];
    int hasArrived;
    int finishTime;
}process;

#define true 1;
#define false 0;

int queRear = 0; //rear index for que
int queIndex = 0; //front index for que. use this or 0
process *que; //que of processes
FILE *outfile;

void FirstComeFirstServe(int,int,process[]);
void RoundRobin(int, int, int, process[]);
void deque();

void main()
{
    //test data
    process p1 = {0, 0, 24, "P1"};
    process p2 = {1, 3, 3, "P2"};
    process p3 = {2, 4, 3, "P3"};
    process p[3]; // set size
    que = p; // set size of que

    //init output File
    outfile = fopen("proceses.txt","w");
    
    process processes[] = { p1, p2, p3 };
    //printf("%d", processes[1].id);
    //RoundRobin(15, 2, 2, processes);
    FirstComeFirstServe(30, 3, processes);
    fclose(outfile);
    
}

void FirstComeFirstServe(int runTill, int num_process, process processes[]){
    
    int time = 0; //current time
    int i = 0; //index for num or processes


	//Lazy way of doing things
	process *finished = processes;
	int finInd = 0;

	fprintf(outfile,"%d processes\n", num_process);
	fprintf(outfile,"Using Round-Robin\n");


    //Loop till end of runTill
    while(time <= runTill)
    {
        //loop through processes
        for(i = 0; i < num_process; i++){
            
            //check if just arrived
            if(processes[i].arrivalTime == time)
            {
		//que it          
		printf("Time %d: %s arrived\n", time, processes[i].name);
		fprintf(outfile,"Time %d: %s arrived\n", time, processes[i].name);
		if(queRear == 0){
			printf("Time %d: %s selected (%d)\n", time, que[0].name, processes[i].burstTime);
time++;
		}
                que[queRear] = processes[i];
                queRear++;   
            }     
        } 
        
        //Is there anything in the que?
        if(queRear != 0){
            //this is the process where the processor Processes the Process
           
            //process the process aka burst time goes down
            que[0].burstTime--;
           
                if(que[0].burstTime == 0){
		    que[0].finishTime = time - que[0].arrivalTime;
		    finished[finInd] = que[0];
		    finInd++;
                    printf("Time %d: %s Finished\n", time, que[0].name);
                    fprintf(outfile,"Time %d: %s Finished\n", time, que[0].name);
		    deque(); // deque current process          
	            if(queRear != 0){      
		    printf("Time %d: %s selected (%d)\n", time, que[0].name, que[0].burstTime);
                    fprintf(outfile,"Time %d: %s selected (%d)\n", time, que[0].name, que[0].burstTime);
		    }
                }
                
                //Are we idling now?
                if(queRear == 0 && time != runTill){
                    printf("Time %d idle\n",time);
                    fprintf(outfile,"Time %d idle\n",time);
                }


            
        }else//nothing in the que
        {
        printf("Time %d idle\n",time);
        fprintf(outfile,"Time %d idle\n",time);
        }
        
        time++; //next time step
    }
    //done
    printf("Finished at time %d\n", time);
    fprintf(outfile,"Finished at time %d\n", time);

	for(i = 0; i < num_process; i++){
		printf("%s wait # turnaround %d\n", finished[i].name, finished[i].finishTime);
	}
}

//RoundRobin implementation
void RoundRobin(int runTill, int num_process, int quantum, process processes[])
{
    
    int time = 0; //current time
    int i = 0; //index for num or processes
    int q = 0; // quantum 

	//Lazy way of doing things
	process *finished = processes;
	int finInd = 0;

	fprintf(outfile,"%d processes\n", num_process);
	fprintf(outfile,"Using Round-Robin\n");
	fprintf(outfile,"Quantum %d\n\n",quantum);

    //Loop till end of runTill
    while(time < runTill)
    {
        //loop through processes
        for(i = 0; i < num_process; i++){
            
            //check if just arrived
            if(processes[i].arrivalTime == time)
            {
                
                    //Que it
		    
                    que[queRear] = processes[i];
                    queRear++;
                printf("Time %d: %s arrived\n", time, processes[i].name);
		fprintf(outfile,"Time %d: %s arrived\n", time, processes[i].name);
                
            }     
        } 
        
        //Is there anything in the que?
        if(queRear != 0){
            //this is the process where the processor Processes the Process
            if(q != 0)
            {
                //if there is something in the queue
                if(queRear != 0){
                    //process the process aka burst time goes down
                    que[0].burstTime--;
                    q--;
                }
                if(que[0].burstTime == 0){
		    que[0].finishTime = time - que[0].arrivalTime;
		    finished[finInd] = que[0];
		    finInd++;
                    printf("Time %d: %s Finished\n", time, que[0].name);
                    fprintf(outfile,"Time %d: %s Finished\n", time, que[0].name);
                    q = 0;
                }
            }
            if(q == 0){

                q = quantum; // reset the quantum
                
                //if more is need que it again
                if(que[0].burstTime > 0){
                    que[queRear] = que[0];
                    queRear++;
                }
                
                deque(); // deque current process
                
                //Are we idling now?
                if(queRear ==0){
                    printf("Time %d idle\n",time);
                    fprintf(outfile,"Time %d idle\n",time);
                }else //nope
                printf("Time %d: %s selected (%d)\n", time, que[0].name, que[0].burstTime);
                fprintf(outfile,"Time %d: %s selected (%d)\n", time, que[0].name, que[0].burstTime);

            }
        }else//nothing in the que
        {
        printf("Time %d idle\n",time);
        fprintf(outfile,"Time %d idle\n",time);
        }
        
        time++; //next time step
    }
    //done
    printf("Finished at time %d\n", time);
    fprintf(outfile,"Finished at time %d\n", time);

	for(i = 0; i < num_process; i++){
		printf("%s wait # turnaround %d\n", finished[i].name, finished[i].finishTime);
	}
}

//simple deque
void deque(){
    int i = 0;
    if(queRear == 0){
        return;
    }
    while(i < queRear){
            que[i] = que[i+1];
            i++;
    }
        queRear--;
    
}
