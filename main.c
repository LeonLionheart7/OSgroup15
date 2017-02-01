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

void RoundRobin(int, int, process[]);

void main()
{
    process p1 = {0, 3, 5, "P1"};
    process p2 = {1, 0, 9, "P2"};
    
    process processes[] = { p1, p2 };
    //printf("%d", processes[1].id);
    RoundRobin(15, 2, processes);
    
}

void RoundRobin(int runTill, int num_process, process processes[])
{
    
    int time = 0; //current time
    int i = 0; //index for num or processes
    int quantum = 2;
    int lowestBurst =0;
    int currentProcess = 0; //current process
    int numOfProcessesLoaded = 0;
    //Loop till end of runTill
    while(time <= runTill)
    {
        //loop through processes
        for(i = 0; i < num_process; i++){
            //check if just arrived
            if(processes[i].arrivalTime == time)
            {
                
                //if there is no current process, assign this to be.
                if(numOfProcessesLoaded == 0){
                    currentProcess = i;
                    lowestBurst = currentProcess;
                    numOfProcessesLoaded++;
                }
                printf("Time %d: %s arrived\n", time, processes[i].name);
                processes[i].hasArrived = true;
            }     
        } 
        
        //this is the process where the processor Processes the Process
        if(quantum != 0)
        {
            processes[currentProcess].burstTime--;
            printf("Time %d: %s burst: %d\n", time, processes[currentProcess].name, processes[currentProcess].burstTime);
            quantum--;
        }
        else{
               
            quantum = 2;
            
            //loop through processes
            for(i = 0; i < num_process; i++)
            {
                if(processes[lowestBurst].burstTime < processes[i].burstTime && currentProcess != lowestBurst){
                    lowestBurst = i;
                }
            }
            currentProcess = lowestBurst;
        }
        time++;
    }
        
}
