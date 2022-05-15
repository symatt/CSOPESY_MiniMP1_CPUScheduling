// Shortest Remaining Time First CPU Scheduling Algorithm

#include<stdio.h>

struct ProcessInfoSRTF {
    int ctr;
    int startTimes[100];
    int endTimes[100];
};

int srtfGetAvgTime(int processes[], int processSize, int arrivalTimes[], int burstTimes[]) {
    int remainingTimes[processSize], waitTimes[processSize], startTime, endTime, i, j, pos, smallest, temp;
    int remain = 0, n, time, sum_wait = 0, sum_turnaround = 0;
    struct ProcessInfoSRTF info[processSize];

    // sort by arrival time and initialize the processInfo struct for multiple start and end times per process
    for (i = 0; i < processSize; i++) {
        pos = i;
        for (j = i + 1; j < processSize; j++) {
            if (arrivalTimes[j] <= arrivalTimes[pos]) 
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
        waitTimes[i] = 0;

        info[i].ctr = 0;
        for (j = 0; j < 100; j++) {
            info[i].startTimes[j] = -1;
            info[i].endTimes[j] = -1;
        }
    }

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
        // printf("CURRENT TIME : %d\n", time);
        // printf("Current smallest: P[%d] burst time: %d arrival time: %d remaining time: %d\n", processes[smallest], burstTimes[smallest], arrivalTimes[smallest], remainingTimes[smallest]);
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
                    info[smallest].ctr += 1;
                    // printf("P[%d] Start Time: %d End Time: %d | Waiting Time: %d\n", smallest + 1, startTime, endTime, endTime-burstTimes[smallest]-arrivalTimes[smallest]);
                    startTime = endTime;
                }
                smallest = i;
                
            }
        }
        // printf("\n");
        
        // if the arrival time of the current smallest is smaller or equal to the current CPU time, subtract 1 from its remaining time
        // else incremenent the start time ( this means that there was an idle CPU time )
        if (arrivalTimes[smallest] <= time) {
            remainingTimes[smallest]--;
        }
        else {
            startTime += 1;
        }

        // printf("NEW smallest: P[%d] burst time: %d arrival time: %d remaining time: %d\n", processes[smallest], burstTimes[smallest], arrivalTimes[smallest], remainingTimes[smallest]);

        // process is finished
        if(remainingTimes[smallest] == 0) {
            remain++;
            endTime = time + 1;
            // printf("\nP[%d] ", processes[smallest]);
            info[smallest].startTimes[info[smallest].ctr] = startTime;
            info[smallest].endTimes[info[smallest].ctr] = endTime;

            // for (i = 0; i < 20; i++) {
            //     if (info[smallest].startTimes[i] == -1 && info[smallest].endTimes[i] == -1) {
            //         break;
            //     }
            //     printf("Start Time: %d End Time: %d | ", info[smallest].startTimes[i], info[smallest].endTimes[i]);
            // }
            // printf("Start Time: %d End Time: %d ", startTime, endTime);
            waitTimes[smallest] = endTime-burstTimes[smallest]-arrivalTimes[smallest];
            // printf("| Waiting Time: %d\n", waitTimes[smallest]);
            sum_wait += waitTimes[smallest];
            
            // make the remaining time a large number to not intefere with the remaining times
            remainingTimes[smallest] = 99999;
            // make the new start time the end time of the finished process
            startTime = endTime;
        }
    }

    struct ProcessInfoSRTF tempInfo;
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
        printf("P[%d] ", processes[i]);
        for (j = 0; j < 20; j++) {
                if (info[i].startTimes[j] == -1 && info[i].endTimes[j] == -1) {
                    break;
                }
                printf("Start Time: %d End Time: %d | ", info[i].startTimes[j], info[i].endTimes[j]);
        }
        printf("| Waiting Time: %d\n", waitTimes[i]);
    }
    
    printf("\nAverage waiting time = %.1f\n", (float)sum_wait / processSize);

    return 0;
}
