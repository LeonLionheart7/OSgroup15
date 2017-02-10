#include<stdio.h>

struct process[] readFile(void);
void runFCFS(struct process[]);
void runRR(struct process[]);
void runSJF(struct process[]);

struct process {
char[] name;
int arrival;
int burst;
};

char mode;
int runTime;
int pCount;
int quantum;
FILE* in;
FILE* out;

void main(void) {
  struct process processes[32];
  
  in = fopen("processes.in", "r")
  if(in==NULL) {
    printf("Error: file not found");
    exit(1);
   }
  else
    processes = readFile();
  fclose(in);
   
  out = fopen("processes.out", "w")
  if(out==NULL) {
    printf("error: file not found");
    exit(1);
  if(mode=='f')
    runFCFS();
  else if(mode=='s');
    runSJF();
  else if(mode=='r');
    runRR();
  else {}
   fclose(out);
   
}

struct process[] readFile(void) {

  char word[128];
  fscanf(in, "%s", &word);
  while(strcmp(word, "end")!=0 {
    if(strcmp(word, "processcount")==0) {
      fscanf(in, %d", &pCount);
    }
    if(strcmp(word, "runfor")==0) {
      fscanf(in, %d", &runTime);
    }
    if(strcmp(word, "use")==0) {
      fscanf(in, %c", &mode);
    }
    if(strcmp(word, "quantum")==0) {
      fscanf(in, %d", &quantum);
    }
  }
  
  struct process processes[pCount];
  int i;
  for(i=0; i<pCount; i++) {
    struct process p;
    fscanf(in, "process name %s arrival %d burst %d", &p.name, &p.arrival, &p.burst);
    processes[i] = p;
  }
  return processes;
}

void runFCFS(struct process[] processes) {
  int time=0;
  int currentP=-1;
  int currentB=0;
  int queue[Pcount];
  int qPlaceCount = 0;
  int qSelectCount = 0;
  
  fprintf(out, "%d processes \n", pCount);
  fprintf(out, "Using First-Come First-Served \n");
  
  while(time<=runTime) {
    int i;
    for(i=0; i<pCount; i++) {
      if(processes[i].arrival==time) {
        fprintf(out, "Time %d: %s arrived \n", time, processes[i].name);
        queue[qPlaceCount] = i;
        qPlaceCount++;
      }
    }
    currentB--;
    
    if(currentB<=0) {
      if(currentP>=0) { //a process had been running
        fprintf(out, "Time %d: %s finished \n", time, processes[currentP].name);
        currentP = -1;
      }
      if(qPlaceCount>qSelectCount) { //a process is in the q
        currentP = queue[qSelectCount];
        currentB = processes[currentP].burst;
        fprintf(out, "Time %d: %s selected (burst %d) \n", time, processes[currentP].name, processes[currentP].burst);
        qselectCount++;
      else
        fprintf(out "Time %d: idle \n", time);
    }
    time++;
}
    }
