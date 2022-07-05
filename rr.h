#ifndef RR_H
#define RR_H
#include "process.h"
/*
    Calculate for total wait time of each process, as well as average waiting time.
    Compute using round robin algorithm.
*/
void solveRR(int X, int Y, int Z, Process processes[]) {
    int i, j, currentTime = 0, totalWait = 0, nDone = 1, start = 0, startIdx = 0, queueCnt = 0, init;
    int queue[5000];
    float average;

    // Sort processes based on arrival time
    sortByArrival(processes, Y);
    // No processes to execute
    if (Y == 0)
        return;
    
    // Initialize remaining time and number of start times and end times for all processes
    for(i = 0; i < Y; i++) {
        processes[i].remainingTime = processes[i].burstTime;
        processes[i].nTimes = 0;
    }
    i = 0;
    queue[0] = i;
    queueCnt += 1;
    i += 1;
    startIdx += 1;
    currentTime = processes[0].arrivalTime;
    while (i < Y && processes[0].arrivalTime == processes[i].arrivalTime) {
        queue[i] = i;
        startIdx += 1;
        queueCnt += 1;
        i++; 
    }
    // Calculate and display total waiting time per process
    while(nDone) {
        // Queue is not empty
        if(start < queueCnt) { 
            // Selected process burst time is more than or equal to the time slice value
            if(processes[queue[start]].remainingTime >= Z) {
                processes[queue[start]].remainingTime = processes[queue[start]].remainingTime - Z;
                processes[queue[start]].times[processes[queue[start]].nTimes].startTime = currentTime;
                currentTime += Z;
                processes[queue[start]].times[processes[queue[start]].nTimes].endTime = currentTime;
                for (j = startIdx; j < Y; j++){
                    if (processes[startIdx].arrivalTime <= currentTime) {
                        queue[queueCnt] = startIdx;
                        queueCnt += 1;
                        startIdx += 1;
                    }
                    else j = Y;
                }
                processes[queue[start]].nTimes += 1;
                // printf("currentTime %d burstTime %d startIdx %d \n", currentTime, processes[queue[start]].burstTime, startIdx);
                // If include current process to ready queue
                processes[queue[start]].waitTime = currentTime - processes[queue[start]].burstTime - processes[queue[start]].arrivalTime;
                if (processes[queue[start]].remainingTime > 0) {
                    queue[queueCnt] = queue[start];
                    queueCnt += 1;
                }
                start += 1;
            } 
            // Selected process burst time is less than the time slice value
            else if(processes[queue[start]].remainingTime > 0) {
                processes[queue[start]].times[processes[queue[start]].nTimes].startTime = currentTime;
                currentTime += processes[queue[start]].remainingTime % Z;
                processes[queue[start]].remainingTime = 0;
                processes[queue[start]].times[processes[queue[start]].nTimes].endTime = currentTime;
                for (j = startIdx; j < Y; j++){
                    if (processes[j].arrivalTime <= currentTime) {
                        queue[queueCnt] = startIdx;
                        queueCnt += 1;
                        startIdx += 1;
                    }
                }
                processes[queue[start]].nTimes += 1;
                // printf("currentTime %d burstTime %d \n", currentTime, processes[queue[start]].burstTime);
                processes[queue[start]].waitTime = currentTime - processes[queue[start]].burstTime - processes[queue[start]].arrivalTime;
                // If include current process to ready queue
                if (processes[queue[start]].remainingTime != 0) {
                    queue[queueCnt] = queue[start];
                    queueCnt += 1;
                }
                start += 1;
            }
        }
        
        // All processes are complete
        else if(startIdx == Y) {
            nDone = 0;
        }
        // No processes in ready queue, add process in queue
        else {
            queue[queueCnt] = startIdx;
            queueCnt += 1;
            startIdx += 1;
            currentTime = processes[queue[start]].arrivalTime;
        }
    }

    sortByProcessId(processes, Y);

    for(i = 0; i < Y; i++) {
        printf("P[%d]", processes[i].processId);
        for (j = 0; j < processes[i].nTimes; j++) {
            printf(" Start Time: %2d End Time: %2d |", processes[i].times[j].startTime, processes[i].times[j].endTime);
        }
        totalWait += processes[i].waitTime;
        printf(" Waiting Time: %2d\n", processes[i].waitTime);
    }

    // Calculate and display average waiting time
    average = (float) totalWait / Y;
    printf("Average waiting time: %.1f\n", average);
}
#endif