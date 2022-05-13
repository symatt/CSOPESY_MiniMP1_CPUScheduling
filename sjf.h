// Shortest Job First CPU Scheduling Algorithm
#include<stdio.h>
int sjfGetAvgTime(int processes[], int processSize, int arrivalTimes[], int burstTimes[]) {
    int waitTimes[processSize], i, j, total = 0, pos, temp;
    float avg_wt;
  
   //sorting of burst times
    for (i = 0; i < processSize; i++) {
        pos = i;
        for (j = i + 1; j < processSize; j++) {
            if (burstTimes[j] < burstTimes[pos]) 
                pos = j;
        }
  
        temp = burstTimes[i];
        burstTimes[i] = burstTimes[pos];
        burstTimes[pos] = temp;
  
        temp = processes[i];
        processes[i] = processes[pos];
        processes[pos] = temp;
    }
   
    waitTimes[0] = 0;            
  
    for (i = 1; i < processSize; i++) {
        waitTimes[i] = 0;
        for (j = 0; j < i; j++)
            waitTimes[i] += burstTimes[j];
  
        total += waitTimes[i];
    }
  
    for (i = 0; i < processSize; i++) {
        int startTime = arrivalTimes[i] + waitTimes[i];
        int endTime = startTime + burstTimes[i];
        printf("P[%d] Start Time: %d End Time: %d | Waiting Time: %d\n", processes[i], startTime, endTime, waitTimes[i]);
    }

    avg_wt = (float)total / processSize; 
    printf("Average Waiting Time: %.1f",avg_wt);

}