// Round Robin CPU Scheduling Algorithm
#include<stdio.h>  
#include<conio.h>  

struct proc {
    int process = 0;
    int burstTime = 0;
    int arrivalTime = 0;
    int counter = 0;
    int startTimes[20];
    int endTimes[20];
    int waitTime = 0;
};

int rrWaitingTime(int processes[], int n, int burstTimes[], int arrivalTimes[], int waitTimes[], int quant, struct proc[]) {
    int index[n], fill = 0, i , j, k;
    int count = 0;
    int clear = 0;

    for (i=0; i<n; i++) {
        proc[i].process = prcesses[i];
        proc[i].burstTime = bursTimes[i];
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
                elif (proc[index[j]].burstTime < quant && proc[index[j]].burstTime > 0) {
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

        for (i=0; i<fill; i++) {
            if (proc[index[i]].burstTime != 0)
                clear = 0;
                break;
            else
                clear = 1;
        }

        for (i=0; i<n; i++) {
            if (arrivalTimes[i] > count) {
                clear = 0;

                break;
            }
        }

    }
    return 0;
}

int rrGetAvgTime(int processes[], int n, int arrivalTimes[], int burstTimes[], int quant) {
    struct proc[n];
    int waitTimes[n], total_wt = 0, total_tat = 0;
    rrWaitingTime(processes, n, burstTimes, arrivalTimes, waitTimes, quant, proc);

    for (int i=0; i<n; i++) {
      total_wt = total_wt + wt[i];
      printf("\t%d\t\t\t%d\t\t\t%d\n",i+1, bt[i], wt[i]);
    }
    printf("Average waiting time = %.1f", (float)total_wt / (float)n);
    return 0;
}
