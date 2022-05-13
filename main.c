#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "fcfs.h"
#include "sjf.h"
#include "srtf.h"
#include "rr.h"

int main() {

    char fileName[30];
    FILE *fptr; 

    // get file name
    printf("Get input here.\n");

    printf("File name: ");
    fgets(fileName, 30, stdin);
    fileName[strcspn(fileName, "\n")] = 0;
    strcat(fileName, ".txt");
    printf("%s\n", fileName);

    // try opening file
    char filePath[30] = "./";
    strcat(filePath, fileName);

    fptr = fopen(filePath, "r");

    if (fptr == NULL) {
        printf("%s not found.\n", fileName);
        exit(1);
    }

    int processSize;
    int algorithm;
    int timeSliceVal;

    int i;
    int index = 0;
    
    // get values for type of algorithm, how many processes, and time slice value
    fscanf(fptr, "%d %d %d", &algorithm, &processSize, &timeSliceVal);
    printf("algorithm: %d, processSize: %d, timeSliceValue: %d\n", algorithm, processSize, timeSliceVal);

    // get the information per process
    int info[processSize*3];
    fscanf (fptr, "%d", &i);   
    while (!feof (fptr)) {  
        // printf ("%d ", i);
        info[index] = i;
        index += 1;
        fscanf (fptr, "%d", &i);      
    }
    
    // separate information into different arrays
    int processes[processSize];
    int arrivalTimes[processSize];
    int burstTimes[processSize];

    index = 0;
    for(i = 0; i < (processSize*3); i+=3) {
        processes[index] = info[i];
        arrivalTimes[index] = info[i+1];
        burstTimes[index] = info[i+2];
        index += 1;
    }

    for (i = 0; i < processSize; i++) printf("\nProcess %d | Arrival Time: %d | Burst Time: %d\n", processes[i], arrivalTimes[i], burstTimes[i]);
    fclose(fptr);


    printf("Execute CPU scheduling algorithm here.\n");
    switch(algorithm) {
        case 0:
            printf("First-Come First-Serve\n");
            fcfsGetAvgTime(processes, processSize, burstTimes);
            break;
        case 1:
            printf("Shortest-Job First\n");
            // sjfGetAvgTime(processes, processSize, burstTimes);
            break;
        case 2:
            printf("Shortest-Remaining-Time-First\n");
            break;
        case 3:
            printf("Round-Robin\n");
            break;
        default:
            printf("Invalid Algorithm\n");
            break;
    }
    
    printf("Show ouput here.\n");
    
    return 0;
}