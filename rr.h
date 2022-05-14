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
    int fill = 0, i, j, k, l, pos, temp;
    int count = 0, fincount = 0, qcount = 0, qpointer = 0;
    int clear = 0, in = 0, qin = 0, inc = 1;
    int index[n];
    int queue[20000];

    for (i=0; i<n; i++) {
        proc[i].counter = 0;
        proc[i].process = processes[i];
        proc[i].burstTime = burstTimes[i];
        proc[i].arrivalTime = arrivalTimes[i];
        proc[i].waitTime = 0;
    }

    //  for (i = 0; i < n; i++) {
    //     pos = i;
    //     for (j = i + 1; j < n; j++) {
    //         if (proc[j].arrivalTime <= proc[pos].arrivalTime) 
    //             pos = j;
    //     }

    //     temp = proc[i].arrivalTime;
    //     proc[i].arrivalTime = proc[pos].arrivalTime;
    //     proc[pos].arrivalTime = temp;
  
    //     temp = proc[i].burstTime;
    //     proc[i].burstTime = proc[pos].burstTime;
    //     proc[pos].burstTime = temp;
  
    //     temp = proc[i].process;
    //     proc[i].process = proc[pos].process;
    //     proc[pos].process = temp;
    // }

    printf("%d\n", n);
    while (clear != 1) {
        do {
            for (i=0; i<n; i++) {
                printf("first loop i: %d\n", i);
                printf("qcount: %d\n", qcount);
                printf("count: %d\n", count);
                printf("arrival time: %d\n", arrivalTimes[i]);
                if (arrivalTimes[i] <= count) {
                    if (fill != 0) {
                        for (j=0; j<fill; j++) {
                            if (index[j] == i) {
                                in = 1;
                                break;
                            }
                        }
                    }
                    if (in == 0) {
                        index[fill] = i;
                        fill++;
                    }
                    in = 0;
                    if (proc[index[i]].burstTime != 0) {
                        queue[qcount] = i;
                        qcount++;
                    }
                }
            }

            if (fincount != n && fill != 0) {
                for (i=0; i<fill; i++) {
                    if (proc[index[i]].burstTime == 0) {
                        inc = 1;
                    }
                    else {
                        inc = 0;
                        break;
                    }
                }
            }
            printf("inc: %d\n", inc);
            if (inc == 1)
                count++;
        } while(inc == 1);

        for (i=qpointer; i<qcount; i++) {
            printf("second loop i: %d\n", i);
            if (proc[queue[i]].burstTime >= quant) {
                proc[queue[i]].startTime[proc[queue[i]].counter] = count;
                proc[queue[i]].burstTime -= quant;
                count += quant;
                proc[queue[i]].endTime[proc[queue[i]].counter] = count;
                proc[queue[i]].counter++;
                for (j=0; j<fill; j++) {
                    if (proc[index[j]].process != proc[queue[i]].process)
                        if (proc[index[j]].burstTime != 0)
                            proc[index[j]].waitTime += quant;
                }
                if (proc[queue[i]].burstTime == 0) {
                    fin[fincount] = queue[i];
                    fincount++;
                }
                for (j=0; j<n; j++) {
                    if (arrivalTimes[j] <= count) {
                        for (k=0; k<fill; k++) {
                            if (index[k] == j) {
                                in = 1;
                                break;
                            }
                        }
                        if (in == 0) {
                            index[fill] = j;
                            proc[index[fill]].waitTime += count - arrivalTimes[j];
                            fill++;
                        }
                        in = 0;
                        if (proc[index[j]].burstTime != 0) {
                            for (l=i; l<qcount; l++) {
                                if (proc[queue[l]].process == proc[index[j]].process) {
                                    qin = 1;
                                    break;
                                }
                            }
                            if (qin == 0) {
                                queue[qcount] = j;
                                qcount++;
                            }
                        }
                        qin = 0;
                    }
                }
            }
            else if (proc[queue[i]].burstTime < quant && proc[queue[i]].burstTime > 0) {
                proc[queue[i]].startTime[proc[queue[i]].counter] = count;
                count += proc[queue[i]].burstTime;
                proc[queue[i]].endTime[proc[queue[i]].counter] = count;
                proc[queue[i]].counter++;
                for (j=0; j<fill; j++) {
                    if (proc[index[j]].process != proc[queue[i]].process)
                        if (proc[index[j]].burstTime != 0)
                            proc[index[j]].waitTime += proc[queue[i]].burstTime;
                }
                proc[queue[i]].burstTime -= proc[queue[i]].burstTime;
                if (proc[queue[i]].burstTime == 0) {
                    fin[fincount] = queue[i];
                    fincount++;
                }
                for (j=0; j<n; j++) {
                    if (arrivalTimes[j] <= count) {
                        for (k=0; k<fill; k++) {
                            if (index[k] == j) {
                                in = 1;
                                break;
                            }
                        }
                        if (in == 0) {
                            index[fill] = j;
                            proc[index[fill]].waitTime += count - arrivalTimes[j];
                            fill++;
                        }
                        in = 0;
                        if (proc[index[j]].burstTime != 0) {
                            for (l=i; l<qcount; l++) {
                                if (proc[queue[l]].process == proc[index[j]].process) {
                                    qin = 1;
                                    break;
                                }
                            }
                            if (qin == 0) {
                                queue[qcount] = j;
                                qcount++;
                            }
                        }
                        qin = 0;
                    }
                }
            }
        }
        qpointer = i;
        if (fincount != n && fill != 0) {
            for (i=0; i<fill; i++) {
                if (proc[index[i]].burstTime == 0) {
                    inc = 1;
                }
                else {
                    inc = 0;
                    break;
                }
            }
        }

        if (inc == 1)
            count++;
        printf("n: %d\n", n);
        printf("fincount: %d\n", fincount);
        if (n == fincount) {
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
