//cpu scheduling

#include <stdio.h>

// Structure to hold process details
struct Process {
    int id; // Process ID
    int burst_time; // Burst time
    int arrival_time; // Arrival time
    int priority; // Priority
};

// Function to sort processes based on burst time
void sort_by_burst_time(struct Process processes[], int n) {
    int i, j;
    struct Process temp;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (processes[j].burst_time > processes[j + 1].burst_time) {
                temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
}

// Function to calculate turnaround time and waiting time for FCFS
void fcfs(struct Process processes[], int n, int turnaround_time[], int waiting_time[]) {
    int i;
    waiting_time[0] = 0;
    turnaround_time[0] = processes[0].burst_time;
    for (i = 1; i < n; i++) {
        waiting_time[i] = waiting_time[i - 1] + processes[i - 1].burst_time;
        turnaround_time[i] = waiting_time[i] + processes[i].burst_time;
    }
}

// Function to calculate turnaround time and waiting time for SJF
void sjf(struct Process processes[], int n, int turnaround_time[], int waiting_time[]) {
    int i;
    sort_by_burst_time(processes, n);
    waiting_time[0] = 0;
    turnaround_time[0] = processes[0].burst_time;
    for (i = 1; i < n; i++) {
        waiting_time[i] = waiting_time[i - 1] + processes[i - 1].burst_time;
        turnaround_time[i] = waiting_time[i] + processes[i].burst_time;
    }
}

// Function to calculate turnaround time and waiting time for Priority
void priority(struct Process processes[], int n, int turnaround_time[], int waiting_time[]) {
    int i;
    // Sort processes based on priority
    for (i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].priority > processes[j + 1].priority) {
                struct Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
    waiting_time[0] = 0;
    turnaround_time[0] = processes[0].burst_time;
    for (i = 1; i < n; i++) {
        waiting_time[i] = waiting_time[i - 1] + processes[i - 1].burst_time;
        turnaround_time[i] = waiting_time[i] + processes[i].burst_time;
    }
}

// Function to calculate turnaround time and waiting time for Round Robin
void round_robin(struct Process processes[], int n, int quantum, int turnaround_time[], int waiting_time[]) {
    int remaining_time[n];
    for (int i = 0; i < n; i++) {
        remaining_time[i] = processes[i].burst_time;
    }
    int t = 0; // Current time
    while (1) {
        int done = 1;
        for (int i = 0; i < n; i++) {
            if (remaining_time[i] > 0) {
                done = 0;
                if (remaining_time[i] > quantum) {
                    t += quantum;
                    remaining_time[i] -= quantum;
                } else {
                    t += remaining_time[i];
                    waiting_time[i] = t - processes[i].burst_time;
                    remaining_time[i] = 0;
                }
            }
        }
        if (done == 1)
            break;
    }
    // Calculate turnaround time
    for (int i = 0; i < n; i++) {
        turnaround_time[i] = waiting_time[i] + processes[i].burst_time;
    }
}

// Function to print table of processes with their turnaround time and waiting time
void print_table(struct Process processes[], int n, int turnaround_time[], int waiting_time[]) {
    printf("\nProcess ID\tBurst Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\n", processes[i].id, processes[i].burst_time, turnaround_time[i], waiting_time[i]);
    }
}

int main() {
    int n, quantum;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    struct Process processes[n];
    int turnaround_time[n], waiting_time[n];

    // Input process details
    for (int i = 0; i < n; i++) {
        printf("Enter details for Process %d:\n", i + 1);
        printf("Burst Time: ");
        scanf("%d", &processes[i].burst_time);
        printf("Arrival Time: ");
        scanf("%d", &processes[i].arrival_time);
        printf("Priority: ");
        scanf("%d", &processes[i].priority);
        processes[i].id = i + 1;
    }

    // Ask for quantum time for Round Robin
    printf("Enter quantum time for Round Robin: ");
    scanf("%d", &quantum);

    // Calculate turnaround time and waiting time for each algorithm
    fcfs(processes, n, turnaround_time, waiting_time);
    printf("\nFCFS Scheduling:\n");
    print_table(processes, n, turnaround_time, waiting_time);

    sjf(processes, n, turnaround_time, waiting_time);
    printf("\nSJF Scheduling:\n");
    print_table(processes, n, turnaround_time, waiting_time);

    priority(processes, n, turnaround_time, waiting_time);
    printf("\nPriority Scheduling:\n");
    print_table(processes, n, turnaround_time, waiting_time);

    round_robin(processes, n, quantum, turnaround_time, waiting_time);
    printf("\nRound Robin Scheduling:\n");
    print_table(processes, n, turnaround_time, waiting_time);

    return 0;
}
