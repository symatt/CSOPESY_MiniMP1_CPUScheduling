// Shortest Remaining Time First CPU Scheduling Algorithm

#include<stdio.h>

struct ProcessInfo {
    int ctr;
    int startTimes[100];
    int endTimes[100];
};

int srtfGetAvgTime(int processes[], int processSize, int arrivalTimes[], int burstTimes[]) {
    int remainingTimes[processSize], startTime, endTime, i, j, pos, smallest, temp;
    int remain = 0, n, time, sum_wait = 0, sum_turnaround = 0;
    struct ProcessInfo info[processSize];

    // sort by arrival time and initialize the processInfo struct for multiple start and end times per process
    for (i = 0; i < processSize; i++) {
        pos = i;
        for (j = i + 1; j < processSize; j++) {
            if (arrivalTimes[j] < arrivalTimes[pos]) 
                pos = j;
        }

        temp = arrivalTimes[i];
        arrivalTimes[i] = arrivalTimes[pos];
        arrivalTimes[pos] = temp;
  
        temp = burstTimes[i];
        burstTimes[i] = burstTimes[pos];
        burstTimes[pos] = temp;
  
        temp = processes[i];
        processes[i] = processes[pos];
        processes[pos] = temp;

        remainingTimes[i] = burstTimes[i];
        info[i].ctr = 0;
        for (j = 0; j < 20; j++) {
            info[i].startTimes[j] = -1;
            info[i].endTimes[j] = -1;
        }
    }

    // printf("\n\nProcess\t|Turnaround Time| Waiting Time\n\n");
    // for (i = 0; i < processSize; i++) {
    //     printf("P[%d] | Burst Time: %d | Arrival Time: %d\n", processes[i], burstTimes[i], arrivalTimes[i]);
    // }
    
    // initialize the smallest value as the first process that arrived
    smallest = 0;
    // initialize the start time to be at time 0
    startTime = 0;

    // loop while there are still processes needed to be executed
    // start from time = 0
    for(time = 0; remain != processSize; time++) {
        // compare if the smallest remaining time process is still the smallest
        for(i = 0; i < processSize; i++) {
            // if not the smallest, make the end time to be the current time and 
            // check if the start != end time ( this means that there are a preemption )
            // make the new start time the current end time
            // make the current index the new smallest remaning time process
            if(arrivalTimes[i] <= time && 
                remainingTimes[i] < remainingTimes[smallest] && 
                remainingTimes[i] > 0) {
                
                // printf("%d =? %d ", smallest + 1, temp + 1);
                    endTime = time;
                    if (startTime != endTime) {
                        info[smallest].startTimes[info[smallest].ctr] = startTime;
                        info[smallest].endTimes[info[smallest].ctr] = endTime;
                        // printf("P[%d] Start Time: %d End Time: %d | Waiting Time: %d\n", smallest + 1, startTime, endTime, endTime-burstTimes[smallest]-arrivalTimes[smallest]);
                        startTime = endTime;
                    }
                smallest = i;
            }
        }
        // printf("\n");

        remainingTimes[smallest]--;

        // process is finished
        if(remainingTimes[smallest] == 0) {
            remain++;
            endTime = time + 1;
            printf("\nP[%d] ", smallest + 1);
            for (i = 0; i < 20; i++) {
                if (info[smallest].startTimes[i] == -1 && info[smallest].endTimes[i] == -1) {
                    break;
                }
                printf("Start Time: %d End Time: %d | ", info[smallest].startTimes[i], info[smallest].endTimes[i]);
            }
            printf("Start Time: %d End Time: %d ", startTime, endTime);
            printf("| Waiting Time: %d\n", endTime-burstTimes[smallest]-arrivalTimes[smallest]);
            sum_wait += (endTime - burstTimes[smallest] - arrivalTimes[smallest]);
            
            // make the remaining time a large number to not intefere with the remaining times
            remainingTimes[smallest] = 9999;
            // make the new start time the end time of the finished process
            startTime = endTime;
        }
    }

    printf("\n\nAverage waiting time = %.1f\n", (float)sum_wait / processSize);


    return 0;
}