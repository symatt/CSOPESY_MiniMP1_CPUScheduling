// Shortest Job First CPU Scheduling Algorithm
#include<stdio.h>

struct ProcessInfoSJF {
    int startTime;
    int endTime;
};

int sjfGetAvgTime(int processes[], int processSize, int arrivalTimes[], int burstTimes[]) {
    int waitTimes[processSize], i, j, total = 0, pos, temp, totalCPUTime = 0, currCPUTime = 0;
    struct ProcessInfoSJF info[processSize];
    float avg_wt;
    
   //sorting of arrival times
    for (i = 0; i < processSize; i++) {
        pos = i;
        for (j = i + 1; j < processSize; j++) {
            if (arrivalTimes[j] < arrivalTimes[pos]) 
                pos = j;
            else if (arrivalTimes[j] == arrivalTimes[pos]) {
                if (burstTimes[j] < burstTimes[pos]) {
                    pos = j;
                }
            }
        }
        // printf("\n");
        temp = burstTimes[i];
        burstTimes[i] = burstTimes[pos];
        burstTimes[pos] = temp;
  
        temp = processes[i];
        processes[i] = processes[pos];
        processes[pos] = temp;

        temp = arrivalTimes[i];
        arrivalTimes[i] = arrivalTimes[pos];
        arrivalTimes[pos] = temp;

        info[i].startTime = 0;
        info[i].endTime = 0;
    }

    // for (i = 0; i < processSize; i++) {
    //     printf("P[%d] | Burst Time: %d | Arrival Time: %d\n", processes[i], burstTimes[i], arrivalTimes[i]);
    // }

    //sorting of arrival times, check id if they should go first
    currCPUTime = burstTimes[0];
    for (i = 1; i < processSize; i++) {
        // printf("currCPUTime : %d\n", currCPUTime);
        pos = i;
        for (j = i + 1; j < processSize; j++) {
            // printf("curr CPU time : %d\n", currCPUTime);
            if (arrivalTimes[j] < arrivalTimes[pos]) 
                pos = j;
            else if (arrivalTimes[j] == arrivalTimes[pos]) {
                if (burstTimes[j] < burstTimes[pos]) {
                    pos = j;
                }
            }

            
            if (arrivalTimes[j] <= currCPUTime && burstTimes[j] < burstTimes[pos]) {
                pos = j;
            }
        }
        // printf("\n");
        temp = burstTimes[i];
        burstTimes[i] = burstTimes[pos];
        burstTimes[pos] = temp;
  
        temp = processes[i];
        processes[i] = processes[pos];
        processes[pos] = temp;

        temp = arrivalTimes[i];
        arrivalTimes[i] = arrivalTimes[pos];
        arrivalTimes[pos] = temp;

        info[i].startTime = 0;
        info[i].endTime = 0;

        currCPUTime += burstTimes[i];
    }

    // for (i = 0; i < processSize; i++) {
    //     printf("P[%d] | Burst Time: %d | Arrival Time: %d\n", processes[i], burstTimes[i], arrivalTimes[i]);
    // }
    
    // initialize waitTime, startTime and endTime of first process
    waitTimes[0] = 0;     
    info[0].startTime = arrivalTimes[0];       
    info[0].endTime = arrivalTimes[0] + burstTimes[0];

    for (i = 1; i < processSize; i++) {

        waitTimes[i] = 0;
        
        // current wait time of process will be the sum of all the end times - the arrival time of the process
        for (j = i - 1; j < i; j++) {
            waitTimes[i] += info[j].endTime - arrivalTimes[i];
            // printf("1 P[%d] wait time: %d\n", i+1, waitTimes[i]);
        }
        // if the process arrived before or at endtime of previous, the start is equal to end of previous
        // else start time will be when the process arrived.
        if (arrivalTimes[i] <= info[i - 1].endTime) {
            info[i].startTime = info[i - 1].endTime;
        }
        else {
            info[i].startTime = arrivalTimes[i];
            waitTimes[i] = 0;
        }
        // end time of process will be start time + burst
        info[i].endTime = info[i].startTime + burstTimes[i];
        total += waitTimes[i];
    }
  
    struct ProcessInfoSJF tempInfo;
     // sort by process id
    for (i = 0; i < processSize; i++) {
        pos = i;
        for (j = i + 1; j < processSize; j++) {
            if (processes[j] <= processes[pos]) 
                pos = j;
        }

        temp = processes[i];
        processes[i] = processes[pos];
        processes[pos] = temp;
  
        temp = waitTimes[i];
        waitTimes[i] = waitTimes[pos];
        waitTimes[pos] = temp;

        tempInfo = info[i];
        info[i] = info[pos];
        info[pos] = tempInfo;
    }

    for (i = 0; i < processSize; i++) {
        printf("P[%d] Start Time: %d End Time: %d | Waiting Time: %d\n", processes[i], info[i].startTime, info[i].endTime, waitTimes[i]);
    }

    avg_wt = (float)total / processSize; 
    printf("Average Waiting Time: %.1f",avg_wt);

}