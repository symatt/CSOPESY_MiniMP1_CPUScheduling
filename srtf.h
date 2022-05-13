// Shortest Remaining Time First CPU Scheduling Algorithm
// Template palang need to adjust pa to specs
// https://www.edureka.co/blog/sjf-scheduling-in-c/
#include<stdio.h>
int srtfGetAvgTime(int processes[], int processSize, int arrivalTimes[], int burstTimes[]) {
    int remainingTimes[processSize + 1], endTime, i, j, pos, smallest, temp;

    int remain = 0, n, time, sum_wait = 0, sum_turnaround = 0;

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
    }

    printf("\n\nProcess\t|Turnaround Time| Waiting Time\n\n");
    for (i = 0; i < processSize; i++) {
        printf("P[%d] | Burst Time: %d | Arrival Time: %d\n", processes[i], burstTimes[i], arrivalTimes[i]);
    }
    
    smallest = 0;
    for(time = 0; remain != processSize; time++) {
        for(i = 0; i < processSize; i++) {
            if(arrivalTimes[i] <= time && 
                remainingTimes[i] < remainingTimes[smallest] && 
                remainingTimes[i] > 0) {
                // endTime = time + 1;
                // printf("\nP[%d] Start Time: End Time: %d | Waiting Time: %d", smallest + 1, endTime, endTime-burstTimes[smallest]-arrivalTimes[smallest]);
                temp = i;
                
                printf("%d =? %d ", smallest + 1, temp + 1);
                // if (smallest != processSize && smallest != temp) {
                    endTime = time + 1;
                    printf("P[%d] Start Time: End Time: %d | Waiting Time: %d\n", smallest + 1, endTime, endTime-burstTimes[smallest]-arrivalTimes[smallest]);
                // }
                smallest = i;
            }
        }
        printf("\n");
        remainingTimes[smallest]--;
        if(remainingTimes[smallest] == 0) {
            remain++;
            endTime = time + 1;
            printf("\n0 rem time P[%d] Start Time: End Time: %d | Waiting Time: %d\n", smallest + 1, endTime, endTime-burstTimes[smallest]-arrivalTimes[smallest]);
            sum_wait += endTime-burstTimes[smallest]-arrivalTimes[smallest];
        }
        // else {
        //     endTime = time + 1;
        //     printf("\nP[%d] Start Time: End Time: %d | Waiting Time: %d", smallest + 1, endTime, endTime-burstTimes[smallest]-arrivalTimes[smallest]);
        // }
    }

    printf("\n\nAverage waiting time = %.1f\n", (float)sum_wait / processSize);


    return 0;
}