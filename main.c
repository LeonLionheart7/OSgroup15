#include <stdio.h>
#include <stdlib.h>

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
void ShortestJobFirst(int, int, process[]);
process* minHeapInsert(process*, process);
process* minHeapDelete(process*);
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
    outfile = fopen("processes.txt","w");

    process processes[] = { p1, p2, p3 };
    //printf("%d", processes[1].id);
    //RoundRobin(15, 2, 2, processes);
    //FirstComeFirstServe(30, 3, processes);
    ShortestJobFirst(35, 3, processes);

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

void ShortestJobFirst(int runTill, int num_process, process processes[]){

    int time = 0; //current time
    int* waits = (int*) malloc(sizeof(int) * num_process);

    process* readyq = malloc(sizeof(process) * num_process);
    readyq[0] = *( (process*) malloc( sizeof(process)) ); //cast & dereference: is there an easier way????
    readyq[0].arrivalTime = 0; //readyq is a min heap, store size in index 0's arrival time

    process current_proc;
    while (time < runTill){

        int j;
        for (j = 0; j < num_process; j++){

            //check if a process starts at this time
            if (processes[j].arrivalTime == time){
                //update hasArrived
                processes[j].hasArrived = 1;
                printf("Time %d: Process %s has arrived.\n", time, processes[j].name);
                //add it to the ready queue
                readyq = minHeapInsert(readyq, processes[j]);
                //printMinHeap(readyq);
            }
        }
        //if no process is currently running and there is a proc in the readyqueue...
        if ( (current_proc.name == NULL || current_proc.finishTime > 0 )&& readyq[0].arrivalTime > 0 ){
            current_proc = readyq[1];
            printf("Time %d: %s started\n", time, current_proc.name);
            waits[current_proc.id] += time - current_proc.arrivalTime - waits[current_proc.id];
            readyq = minHeapDelete(readyq);
        }
        //else if there's a proc running & one in the ready queue
        else if ( (current_proc.name != NULL && current_proc.finishTime == 0) && readyq[1].name != NULL){

            //if readyq top is shorter, stop current proc, add to readyq, start new proc
            if (readyq[1].burstTime < current_proc.burstTime){
                process tmp = current_proc;
                current_proc = readyq[1];
                printf("Time %d: %s started\n", time, current_proc.name);
                waits[current_proc.id] += time - current_proc.arrivalTime - waits[current_proc.id];
                readyq = minHeapDelete(readyq);
                readyq = minHeapInsert(readyq, tmp);
            }
        }

        //print & decrement current proc's burst time
        if (current_proc.name == NULL || current_proc.finishTime > 0){
            printf("Time %d: IDLE\n", time);
        }
        else {
            if (current_proc.burstTime == 0){
                printf("Time %d: %s finished.\n", time, current_proc.name);
                current_proc.finishTime = time;
                processes[current_proc.id] = current_proc;
            }
            current_proc.burstTime--;
        }
        time++;
    }

    if (current_proc.burstTime > 0 || readyq[0].arrivalTime != 0){
        printf("current proc %s burst time: %d\n", current_proc.name, current_proc.burstTime);
        printf("Procs in ready queue: %d\n", readyq[0].arrivalTime);
        printf("Failure: SJF did not complete.\n");
    }

    else{
        printf("\n");
        int k;
        for (k = 0; k < num_process; k++){
            printf("%s wait %d, turnaround %d\n", processes[k].name, waits[k], processes[k].finishTime - processes[k].arrivalTime);
        }
    }
}

void printMinHeap(process* processes){
    int length = processes[0].arrivalTime;
    printf("%d processes in readyq\n", length);
    if (length == 0){
        return;
    }
    else{
        int j;
        for (j = 1; j <= length; j++){
            printf("[ %s : %d ] ", processes[j].name, processes[j].burstTime);
        }
        printf("\n");
    }
}

process* minHeapInsert(process* processes, process new_proc){
    //get size & increment
    int l = ++(processes[0].arrivalTime);
    //add new process to minheap
    processes[l] = new_proc;
    //percolate up
    while(l/2 > 0){
        if (processes[l].burstTime < processes[l/2].burstTime){
            process tmp = processes[l/2];
            processes[l/2] = processes[l];
            processes[l] = tmp;
        }
        l = l/2;
    }
    //return pointer to top of heap
    return processes;
}

//deletes and returns a pointer to
process* minHeapDelete(process* processes){
    //get size & decrement
    int l = --(processes[0].arrivalTime);
    //copy last of heap into top spot
    processes[1] = processes[l+1];
    //percolate down
    int x=1;
    while(x <= (l/2)){
        //get index of leftchild
        int swapindex = 2*x;
        //check if rightchild exists, compare if is does
        if (swapindex + 1 <= l &&
            processes[swapindex+1].burstTime < processes[swapindex].burstTime){
                swapindex = swapindex+1;
            }
        //if smallest child is smaller than x, swap
        if (processes[x].burstTime > processes[swapindex].burstTime){
            process tmp = processes[x];
            processes[x] = processes[swapindex];
            processes[swapindex] = tmp;
            x = swapindex;
        }
        //if not smaller, move x out of range
        else {
            x = l;
        }
    }
    return processes;
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
