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

int rrWaitingTime(int processes[], int n, int burstTimes[], int arrivalTimes[], int waitTimes[], int quant, struct Proc proc[], int index[]) {
    int fill = 0, i, j, k;
    int count = 0;
    int clear = 0;

    for (i=0; i<n; i++) {
        proc[i].process = 0;
        proc[i].burstTime = 0;
        proc[i].arrivalTime = 0;
        proc[i].process = processes[i];
        proc[i].burstTime = burstTimes[i];
        proc[i].arrivalTime = arrivalTimes[i];
    }

    while (clear != 1) {
        clear = 0;
        for (i=0; i<=fill; i++) {
            for (j=0; j<n; j++) {
                if (arrivalTimes[j] <= count) {
                    for (k=0; k<fill; k++) {
                        if (index[fill] != count) {
                            index[fill] = j;
                            fill++;
                        }
                    }
                }
            }

            for (j=0; j<fill; j++) {
                if (proc[index[j]].burstTime >= quant) {
                    proc[index[j]].startTime[proc[index[j]].counter] = count;
                    proc[index[j]].burstTime -= quant;
                    count += quant;
                    proc[index[j]].endTime[proc[index[j]].counter] = count;
                    proc[index[j]].counter++;
                    for (k=0; k<fill; k++) {
                        if (proc[index[k]].process != proc[index[j]].process)
                            proc[index[k]].waitTime += quant;
                    }
                }
                else if (proc[index[j]].burstTime < quant && proc[index[j]].burstTime > 0) {
                    proc[index[j]].startTime[proc[index[j]].counter] = count;
                    count += proc[index[j]].burstTime;
                    proc[index[j]].burstTime -= proc[index[j]].burstTime;
                    proc[index[j]].endTime[proc[index[j]].counter] = count;
                    proc[index[j]].counter++;
                    for (k=0; k<fill; k++) {
                        if (proc[index[k]].process != proc[index[j]].process)
                            proc[index[k]].waitTime += proc[index[j]].burstTime;
                    }
                }
            }

        }
        // printf("NICE\n");
        for (i=0; i<fill; i++) {
            if (proc[index[i]].burstTime != 0) {
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
    int index[n];
    int waitTimes[n], total_wt = 0, total_tat = 0, i, j;
    rrWaitingTime(processes, n, burstTimes, arrivalTimes, waitTimes, quant, proc, index);
    
    for (i=0; i<n; i++) {
      total_wt = total_wt + proc[index[i]].waitTime;
      printf("P[%d] ", proc[index[i]].process);
      for (j=0; j<proc[index[i]].counter; j++) {
          printf("Start Time: %d  End Time: %d  |  ", proc[index[i]].startTime[j], proc[index[i]].endTime[j]);
      }
      printf("Wait Time: %d\n", proc[index[i]].waitTime);
    }
    printf("Average waiting time = %.1f", (float)total_wt / (float)n);
    return 0;
}
