// First Come First Serve CPU Scheduling Algorithm
#include <stdio.h>

int procTime(int proc[], int n, int arrival_time[], int burst_time[], int wait_time[], int start_time[], int end_time[]) {
    int i, cpu;
    int clear = 0, pass = 0;
    cpu = arrival_time[0];

    do {
        for (i=0; i<n; i++) {
            if (arrival_time[i] <= cpu && burst_time[i] != 0) {
                pass = 1;
                break;
            }
        }

        if (pass == 0) {
            cpu++;
        }

        if (pass == 1) {
            start_time[i] = cpu;
            end_time[i] = start_time[i] + burst_time[i];
            wait_time[i] = cpu - arrival_time[i];
            cpu += burst_time[i];
            burst_time[i] -= burst_time[i];
        }

        for (i = 0; i < n; i++) {
            if (burst_time[i] == 0) {
                clear = 1;
            }
            else  {
                clear = 0;
                break;
            }
        }

    } while (clear != 1);
    return 0;
}

int fcfsGetAvgTime(int proc[], int n, int arrivalTime[], int burst_time[]) {
    int wait_time[n], start_time[n], end_time[n], total_wt = 0, temp = 0;
    int i, j;
    
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (arrivalTime[j] > arrivalTime[i]) {
                temp = proc[i];
                proc[i] = proc[j];
                proc[j] = temp;

                temp = arrivalTime[i];
                arrivalTime[i] = arrivalTime[j];
                arrivalTime[j] = temp;

                temp = burst_time[i];
                burst_time[i] = burst_time[j];
                burst_time[j] = temp;
            }
        }
    }

    procTime(proc, n, arrivalTime, burst_time, wait_time, start_time, end_time);

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (proc[j] > proc[i]) {
                temp = proc[i];
                proc[i] = proc[j];
                proc[j] = temp;

                temp = arrivalTime[i];
                arrivalTime[i] = arrivalTime[j];
                arrivalTime[j] = temp;

                temp = burst_time[i];
                burst_time[i] = burst_time[j];
                burst_time[j] = temp;
            }
        }
    }

    for (i = 0; i < n; i++) {
        total_wt = total_wt + wait_time[i];
        printf("P[%d]  Start Time:  %d  End Time:  %d  |  Waiting Time: %d\n", i, start_time[i], end_time[i], wait_time[i]);
    }

    printf("Average waiting time = %.1f\n", (float)total_wt / (float)n);
    return 0;
}
