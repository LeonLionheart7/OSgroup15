#include <stdio.h>

typedef struct process
{
    int id;
    int arrivalTime;
    int burstTime;
    char name[10];
    int hasArrived;
}process;

#define true 1;
#define false 0;

int queRear = 0;
int queIndex = 0;
process *que;

void RoundRobin(int, int, process[]);
void deque();

void main()
{
    process p1 = {0, 3, 5, "P1"};
    process p2 = {1, 0, 9, "P2"};
    
    process q[2];
    que = q;
    
    process processes[] = { p1, p2 };
    //printf("%d", processes[1].id);
    RoundRobin(15, 2, processes);
    
}

void RoundRobin(int runTill, int num_process, process processes[])
{
    
    int time = 0; //current time
    int i = 0; //index for num or processes
    int quantum = 0;
    int lowestBurst =0;
    int currentProcess = 0; //current process
    int numOfProcessesLoaded = 0;
    process queue[num_process];
    //Loop till end of runTill
    while(time < runTill)
    {
        //loop through processes
        for(i = 0; i < num_process; i++){
            
            //check if just arrived
            if(processes[i].arrivalTime == time)
            {
                
                //if there is no current process, assign this to be.
                if(numOfProcessesLoaded == 0){
                    //Que it
                    que[queRear] = processes[i];
                    queRear++;
                }
                printf("Time %d: %s arrived\n", time, processes[i].name);
                processes[i].hasArrived = true;
            }     
        } 
        
        if(queRear != 0){
            //this is the process where the processor Processes the Process
            if(quantum != 0)
            {
                if(queRear != 0){
            
                    que[0].burstTime--;
                    quantum--;
                }
                if(que[0].burstTime == 0){
                    printf("Time %d: %s Finished\n", time, que[0].name);
                    quantum = 0;
                }
            }
            if(quantum == 0){
                if(que[0].burstTime == 0){
                    printf("Time %d: %s Finished\n", time, que[0].name);
                }
            
                quantum = 2;
                if(que[0].burstTime > 0){
                    que[queRear] = que[0];
                    //printf("Time %d: %s selected (%d)\n", time, que[0].name, que[0].burstTime);
                    queRear++;
                }
                deque();
                if(queRear ==0){
                    printf("Time %d idle\n",time);
                }else
                printf("Time %d: %s selected (%d)\n", time, que[0].name, que[0].burstTime);

            }
        }else{
        printf("Time %d idle\n",time);
        }
        time++;
    }
        printf("Finished at time %d\n", time);
}

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
