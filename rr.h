// Round Robin CPU Scheduling Algorithm
#include<stdio.h>  
#include<conio.h>  

struct ProcRR {
    int process;
    int burstTime;
    int arrivalTime;
    int counter;
    int startTime[100];
    int endTime[100];
    int waitTime;
    int adjust;
};

int rrWaitingTime(int n, int quant, struct ProcRR proc[]) {
   int i, j, k;
   int queue[2000], qcount = 1, qpointer = 0, qin = 0;
   int clear = 0, pass = 0, ctr = 0, temp, newcount = 0;
   int cpu = proc[0].arrivalTime;

//    queue[0] = 0;
//    proc[0].adjust = 1;

   do {
       for (i=0; i<n; i++) {
            if (proc[i].arrivalTime <= cpu && proc[i].burstTime != 0) {
                pass = 1;
                break;
            }
            else
                pass = 0;
        }

        if (pass == 0) 
            cpu++;

        // add to queue
        qcount = 0;
        newcount = 0;
        for (j = 0; j < n; j++) {
            if(proc[j].arrivalTime <= cpu && proc[j].burstTime != 0) {
                queue[qcount] = j;
                
                if (proc[j].adjust == 0) {
                    temp = queue[qcount];
                    queue[qcount] = queue[newcount];
                    queue[newcount] = temp;

                    for (k = qcount; k > newcount + 1; k--) {
                        temp = queue[k];
                        queue[k] = queue[k-1];
                        queue[k-1] = temp;
                    }
                    newcount++;
                    proc[j].waitTime += cpu - proc[j].arrivalTime;
                    proc[j].adjust = 1;
                }
                qcount++;
            }
            printf("Q[%d]: %d\n", j, queue[j]);
        }
        printf("\n");

        if (pass == 1) {
            for (i=0; i<qcount; i++) {
                printf("P[%d]: %d\n", i, proc[queue[i]].process);
                proc[queue[i]].startTime[proc[queue[i]].counter] = cpu;
                
                if (proc[queue[i]].burstTime >= quant) {
                    for (j=0; j<n; j++) {
                        if (proc[queue[i]].process != proc[j].process && proc[j].burstTime != 0 && proc[j].arrivalTime <= cpu)
                            proc[j].waitTime += quant;
                    }
                    proc[queue[i]].endTime[proc[queue[i]].counter] = cpu + quant;
                    cpu += quant;
                    proc[queue[i]].burstTime -= quant;
                }
                else  {
                    for (j=0; j<n; j++) {
                        if (proc[queue[i]].process != proc[j].process && proc[j].burstTime != 0 && proc[j].arrivalTime <= cpu)
                            proc[j].waitTime += proc[queue[i]].burstTime;
                    }
                    proc[queue[i]].endTime[proc[queue[i]].counter] = cpu + proc[queue[i]].burstTime;
                    cpu += proc[queue[i]].burstTime;
                    proc[queue[i]].burstTime -= proc[queue[i]].burstTime;
                }
                (proc[queue[i]].counter)++;

                // // add to queue
                // for (j=0; j<n; j++) {
                //     printf("j: %d ", j);
                //     printf("j arrival: %d ", proc[j].arrivalTime);
                //     printf("j burst: %d ", proc[j].burstTime);
                //     printf("cpu: %d ", cpu);
                //     if (proc[j].arrivalTime <= cpu && proc[j].burstTime != 0) {
                //         // if (proc[i].process != proc[j].process) {
                //             queue[qcount] = j;
                //             qcount++;
                //             if (proc[j].adjust == 0) {
                //                 proc[j].waitTime += cpu - proc[j].arrivalTime;
                //                 proc[j].adjust = 1;
                //             }
                //         // }
                //         // else {
                //         //     if (proc[j].burstTime != 0) {
                //         //         printf("HELLO ");
                //         //         queue[qcount] = j;
                //         //         qcount++;
                //         //     }
                //         // }
                //     }
                //     // printf("queue %d ", queue[j]);
                    
                //     // printf("qptr %d ", qpointer);
                // }

                // for (k = 0; k < qcount; k++) printf("\nqueue index : %d\n", queue[k]);
                // printf("1 qptr %d ", qpointer);
                // printf("\n");

                

            }
            // qpointer = i;
            // printf("2 qptr %d\n", qpointer);
            // printf("HELLO ");
        }

       for (i = 0; i < n; i++) {
        //    printf("bt %d: %d ", i, proc[i].burstTime);
            if (proc[i].burstTime == 0) {
                clear = 1;
            }
            else  {
                clear = 0;
                break;
            }
        }
   } while (clear != 1);
}

int rrGetAvgTime(int processes[], int n, int arrivalTimes[], int burstTimes[], int quant) {
    struct ProcRR proc[n];
    int total_wt = 0, total_tat = 0;
    int i, j, k;
    struct ProcRR temp;


    // insert to struct
    for (i=0; i<n; i++) {
        proc[i].process = processes[i];
        proc[i].burstTime = burstTimes[i];
        proc[i].arrivalTime = arrivalTimes[i];
        proc[i].counter = 0;
        proc[i].waitTime = 0;
        proc[i].adjust = 0;
        
        for (j=0; j<100; j++) {
            proc[i].startTime[j] = 0;
            proc[i].endTime[j] = 0;
        }
    }

    // sort by arrival time
    for (i=0; i<n; i++) {
        for (j=0; j<n; j++) {
            if (proc[j].arrivalTime > proc[i].arrivalTime) {
                temp = proc[i];
                proc[i] = proc[j];
                proc[j] = temp;  
            }
        }
    }
    // int pos;
    // for (i = 0; i < n; i++) {
    //     pos = i;
    //     for (j = i + 1; j < n; j++) {
    //         if (proc[j].arrivalTime <= proc[i].arrivalTime) 
    //             pos = j;
    //     }
    //     temp = proc[i];
    //     proc[i] = proc[pos];
    //     proc[pos] = temp;
    // }

    for (i = 0; i < n; i++) {
        printf("P[%d] | Burst Time: %d | Arrival Time: %d\n", proc[i].process, proc[i].burstTime, proc[i].arrivalTime);
    }
    

    rrWaitingTime(n, quant, proc);

    // sort by process id
    for (i=0; i<n; i++) {
        for (j=0; j<n; j++) {
            if (proc[j].process > proc[i].process) {
                temp = proc[i];
                proc[i] = proc[j];
                proc[j] = temp;  
            }
        }
    }
    
    // print
    for (i=0; i<n; i++) {
      total_wt = total_wt + proc[i].waitTime;
      printf("P[%d] ", proc[i].process);
      for (j=0; j<proc[i].counter; j++) {
          printf("Start Time: %d  End Time: %d  |  ", proc[i].startTime[j], proc[i].endTime[j]);
      }
      printf("Wait Time: %d\n\n", proc[i].waitTime);
    }
    printf("Average waiting time = %.1f", (float)total_wt / (float)n);
    return 0;
}
