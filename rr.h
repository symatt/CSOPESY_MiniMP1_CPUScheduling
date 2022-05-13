// Round Robin CPU Scheduling Algorithm
#include<stdio.h>  
#include<conio.h>  

struct Proc {
    int process;
    int burstTime;
    int arrivalTime;
    int counter;
    int startTime[20];
    int endTime[20];
    int waitTime;
};

int rrWaitingTime(int processes[], int n, int burstTimes[], int arrivalTimes[], int waitTimes[], int quant, struct Proc proc[], int fin[]) {
    int fill = 0, i, j, k;
    int count = 0, fincount = 0;
    int clear = 0;
    int index[n];

    for (i=0; i<n; i++) {
        proc[i].process = 0;
        proc[i].burstTime = 0;
        proc[i].arrivalTime = 0;
        proc[i].counter = 0;
        proc[i].process = processes[i];
        proc[i].burstTime = burstTimes[i];
        proc[i].arrivalTime = arrivalTimes[i];
        proc[i].waitTime = 0;
    }

    while (clear != 1) {
        clear = 0;
        for (i=0; i<n; i++) {
            if (arrivalTimes[i] <= count) {
                for (j=0; j<fill; j++) {
                    if (index[fill] != count) {
                        index[fill] = i;
                        fill++;
                    }
                }
            }
        }

            
        for (i=0; i<fill; i++) {
            if (proc[index[i]].burstTime >= quant) {
                proc[index[i]].startTime[proc[index[i]].counter] = count;
                proc[index[i]].burstTime -= quant;
                count += quant;
                proc[index[i]].endTime[proc[index[i]].counter] = count;
                proc[index[i]].counter++;
                for (j=0; j<fill; j++) {
                    if (proc[index[j]].process != proc[index[i]].process)
                        proc[index[j]].waitTime += quant;
                }
                if (proc[index[i]].burstTime == 0) {
                    fin[fincount] = index[i];
                    fincount++;
                }
            }
            else if (proc[index[i]].burstTime < quant && proc[index[j]].burstTime > 0) {
                proc[index[i]].startTime[proc[index[i]].counter] = count;
                count += proc[index[i]].burstTime;
                proc[index[i]].burstTime -= proc[index[i]].burstTime;
                proc[index[i]].endTime[proc[index[i]].counter] = count;
                proc[index[i]].counter++;
                for (j=0; j<fill; j++) {
                    if (proc[index[j]].process != proc[index[i]].process)
                        proc[index[j]].waitTime += proc[index[i]].burstTime;
                }
                if (proc[index[i]].burstTime == 0) {
                    fin[fincount] = index[i];
                    fincount++;
                }
            }
        }

        printf("NICE\n");
        for (i=0; i<n; i++) {
            if (proc[i].burstTime != 0) {
                clear = 0;
                break;
            }
            else
                clear = 1;
        }
    }
    return 0;
}

int rrGetAvgTime(int processes[], int n, int arrivalTimes[], int burstTimes[], int quant) {
    struct Proc proc[n];
    int fin[n];
    int waitTimes[n], total_wt = 0, total_tat = 0, i, j;
    rrWaitingTime(processes, n, burstTimes, arrivalTimes, waitTimes, quant, proc, fin);
    
    for (i=0; i<n; i++) {
      total_wt = total_wt + proc[fin[i]].waitTime;
      printf("P[%d] ", proc[fin[i]].process);
      for (j=0; j<proc[fin[i]].counter; j++) {
          printf("Start Time: %d  End Time: %d  |  ", proc[fin[i]].startTime[j], proc[fin[i]].endTime[j]);
      }
      printf("Wait Time: %d\n", proc[fin[i]].waitTime);
    }
    printf("Average waiting time = %.1f", (float)total_wt / (float)n);
    return 0;
}
