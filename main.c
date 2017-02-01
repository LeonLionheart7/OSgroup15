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

int queRear = 0; //rear index for que
int queIndex = 0; //front index for que. use this or 0
process *que; //que of processes

void RoundRobin(int, int, int, process[]);
void deque();

void main()
{
    //test data
    process p1 = {0, 3, 5, "P1"};
    process p2 = {1, 0, 9, "P2"};
    process p[2]; // set size
    que = p; // set size of que
    
    process processes[] = { p1, p2 };
    //printf("%d", processes[1].id);
    RoundRobin(15, 2, 2, processes);
    
}

//RoundRobin implementation
void RoundRobin(int runTill, int num_process, int quantum, process processes[])
{
    
    int time = 0; //current time
    int i = 0; //index for num or processes
    int q = 0; // quantum 

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
                processes[i].hasArrived = true;
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
                    printf("Time %d: %s Finished\n", time, que[0].name);
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
                }else //nope
                printf("Time %d: %s selected (%d)\n", time, que[0].name, que[0].burstTime);

            }
        }else//nothing in the que
        {
        printf("Time %d idle\n",time);
        }
        
        time++; //next time step
    }
    //done
    printf("Finished at time %d\n", time);
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
