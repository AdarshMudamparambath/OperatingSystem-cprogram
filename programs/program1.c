#include <stdio.h> 
void sortByArrivalTime(int at[], int bt[], int pid[], int numProcesses); 
int main() { 
    int numProcesses; 
    printf("Enter the number of processes: "); 
    scanf("%d", &numProcesses); 
    int at[numProcesses]; // arrival times 
    int bt[numProcesses]; // burst times 
    int pid[numProcesses]; // process IDs 
    for (int i = 0; i < numProcesses; i++) { 
        printf("Process %d:\n", i + 1); 
        printf("Enter Arrival Time: "); 
        scanf("%d", &at[i]); 
        printf("Enter Burst Time: "); 
        scanf("%d", &bt[i]); 
        pid[i] = i + 1; 
    } 
    sortByArrivalTime(at, bt, pid, numProcesses); 
    int ct[numProcesses]; // completion times 
    int tat[numProcesses]; // turnaround times 
    int wt[numProcesses]; // waiting times 
    int totalWt = 0; 
    int totalTat = 0; 
    int currentTime = 0; 
    for (int i = 0; i < numProcesses; i++) { 
        currentTime = (currentTime > at[i]) ? currentTime : at[i]; 
        ct[i] = currentTime + bt[i]; 
        tat[i] = ct[i] - at[i]; 
        wt[i] = tat[i] - bt[i]; 
        totalWt += wt[i]; 
        totalTat += tat[i]; 
        currentTime = ct[i]; 
    } 
    double avgWt = (double) totalWt / numProcesses; 
    double avgTat = (double) totalTat / numProcesses; 
    printf("\nProcess\t Arrival Time\t Burst Time\t Completion Time\t 
Turnaround Time\t Waiting Time\n"); 
    for (int i = 0; i < numProcesses; i++) { 
        printf("%d\t\t%d\t\t\t%d\t\t\t%d\t\t\t\t%d\t\t\t\t%d\n", pid[i], at[i], bt[i], 
ct[i], tat[i], wt[i]); 
    } 
    printf("\nAverage Waiting Time: %.2lf\n", avgWt); 
    printf("Average Turnaround Time: %.2lf\n", avgTat); 
 
  return 0;   
} 
void sortByArrivalTime(int at[], int bt[], int pid[], int numProcesses) { 
    for (int i = 0; i < numProcesses - 1; i++) { 
        for (int j = 0; j < numProcesses - i - 1; j++) { 
            if (at[j] > at[j + 1]) { 
                int tempAt = at[j]; 
                at[j] = at[j + 1]; 
                at[j + 1] = tempAt; 
                int tempBt = bt[j]; 
                bt[j] = bt[j + 1]; 
                bt[j + 1] = tempBt; 
                int tempPid = pid[j]; 
                pid[j] = pid[j + 1]; 
                pid[j + 1] = tempPid; 
            } 
        } 
    } 
} 
