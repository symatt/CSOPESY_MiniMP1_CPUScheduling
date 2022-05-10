#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "fcfs.h"
#include "sjf.h"
#include "srtf.h"
#include "rr.h"

struct processInfo {
    int processNum;
    int arrivalTime;
    int burstTime;
    int waitTime;
    int startTime;
    int endTime;
};

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
    
    // turn into a struct for easier processing later
    struct processInfo processes[processSize];

    index = 0;
    for(i = 0; i < (processSize*3); i+=3) {
        processes[index].processNum = info[i];
        processes[index].arrivalTime = info[i];
        processes[index].burstTime = info[i];
        index += 1;
    }

    for (i = 0; i < processSize; i++) printf("\nProcess %d | Arrival Time: %d | Burst Time: %d\n", processes[i].processNum, processes[i].arrivalTime, processes[i].burstTime);
    fclose(fptr);


    printf("Execute CPU scheduling algorithm here.\n");
    printf("Show ouput here.\n");
    
    return 0;
}