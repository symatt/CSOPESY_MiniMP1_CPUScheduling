// Round Robin CPU Scheduling Algorithm
#include<stdio.h>  
#include<conio.h>  

struct Proc {
    int process;
    int burstTime;
    int arrivalTime;
    int counter;
    int startTime[100];
    int endTime[100];
    int waitTime;
};

int rrWaitingTime(int processes[], int n, int burstTimes[], int arrivalTimes[], int waitTimes[], int quant, struct Proc proc[], int fin[]) {
    int fill = 0, i, j, k;
    int count = 0, fincount = 0;
    int clear = 0, in = 0;
    int index[n];

    for (i=0; i<n; i++) {
        proc[i].counter = 0;
        proc[i].process = processes[i];
        proc[i].burstTime = burstTimes[i];
        proc[i].arrivalTime = arrivalTimes[i];
        proc[i].waitTime = 0;
    }

    while (clear != 1) {
        for (i=0; i<n; i++) {
            if (arrivalTimes[i] <= count) {
                for (j=0; j<fill; j++) {
                    if (index[j] == i) {
                        in = 1;
                        break;
                    }
                }
                if (in == 0) {
                    index[fill] = i;
                    fill++;
                }
                in = 0;
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
                        if (proc[index[j]].burstTime != 0)
                            proc[index[j]].waitTime += quant;
                }
                if (proc[index[i]].burstTime == 0) {
                    fin[fincount] = index[i];
                    fincount++;
                }
            }
            else if (proc[index[i]].burstTime < quant && proc[index[i]].burstTime > 0) {
                proc[index[i]].startTime[proc[index[i]].counter] = count;
                count += proc[index[i]].burstTime;
                proc[index[i]].burstTime -= proc[index[i]].burstTime;
                proc[index[i]].endTime[proc[index[i]].counter] = count;
                proc[index[i]].counter++;
                for (j=0; j<fill; j++) {
                    if (proc[index[j]].process != proc[index[i]].process)
                        if (proc[index[j]].burstTime != 0)
                            proc[index[j]].waitTime += proc[index[i]].burstTime;
                }
                if (proc[index[i]].burstTime == 0) {
                    fin[fincount] = index[i];
                    fincount++;
                }
            }
        }

        if (fill == fincount) {
            clear = 1;
        }
        else clear = 0;
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
      printf("P[%d] ", fin[i]);
      for (j=0; j<proc[fin[i]].counter; j++) {
          printf("Start Time: %d  End Time: %d  |  ", proc[fin[i]].startTime[j], proc[fin[i]].endTime[j]);
      }
      printf("Wait Time: %d\n\n", proc[fin[i]].waitTime);
    }
    printf("Average waiting time = %.1f", (float)total_wt / (float)n);
    return 0;
}
