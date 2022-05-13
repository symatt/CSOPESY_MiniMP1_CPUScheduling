// First Come First Serve CPU Scheduling Algorithm
#include <stdio.h>

int waitingTime(int proc[], int n, int burst_time[], int wait_time[]) {
    wait_time[0] = 0;
    for (int i = 1; i < n; i++ )
        wait_time[i] = burst_time[i-1] + wait_time[i-1];
    return 0;
}

int procTime(int proc[], int n, int burst_time[], int start_time[], int end_time[]) {
    start_time[0] = 0;
    end_time[0] = start_time[0] + burst_time[0];
    for (int i = 1; i < n; i++ ) {
        start_time[i] = end_time[i-1];
        end_time[i] = start_time[i] + burst_time[i];
    }
    
    return 0;
}

int fcfsGetAvgTime(int proc[], int n, int burst_time[]) {
    int wait_time[n], start_time[n], end_time[n], total_wt = 0;
    int i;

    waitingTime(proc, n, burst_time, wait_time);
    printf("Processes  Burst   Waiting  Turn around \n");

    for (i = 0; i < n; i++) {
        total_wt = total_wt + wait_time[i];
        printf("P[%d]  Start Time:  %d  End Time:  %d  |  Waiting Time: %d\n", i, start_time[i], end_time[i], wait_time[i]);
    }

    printf("Average waiting time = %.1f\n", (float)total_wt / (float)n);
    return 0;
}