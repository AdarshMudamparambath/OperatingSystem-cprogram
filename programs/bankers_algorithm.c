//Bankers algorithm

#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

// Available resources
int available[MAX_RESOURCES];

// Maximum resources each process can claim
int maximum[MAX_PROCESSES][MAX_RESOURCES];

// Currently allocated resources to each process
int allocation[MAX_PROCESSES][MAX_RESOURCES];

// Remaining resources needed by each process
int need[MAX_PROCESSES][MAX_RESOURCES];

// Number of processes and resources
int num_processes, num_resources;

// Function prototypes
void initialize();
void input();
bool request_resources(int process_id, int request[]);
void release_resources(int process_id, int release[]);
bool is_safe();

int main() {
    initialize();
    input();

    // Check if the initial state is safe
    if (is_safe()) {
        printf("Initial state is safe.\n");
    } else {
        printf("Initial state is not safe. Exiting...\n");
        return 1;
    }

    int process_id;
    int request[MAX_RESOURCES];

    // Simulate resource requests and releases
    while (true) {
        printf("Enter process id (0 to %d) or -1 to exit: ", num_processes - 1);
        scanf("%d", &process_id);

        if (process_id == -1)
            break;

        printf("Enter request for resources (up to %d): ", num_resources);
        for (int i = 0; i < num_resources; i++)
            scanf("%d", &request[i]);

        // Try to allocate resources
        if (request_resources(process_id, request)) {
            printf("Resources allocated successfully.\n");
        } else {
            printf("Resource allocation failed. Exiting...\n");
            return 1;
        }

        // Check if the current state is safe
        if (is_safe()) {
            printf("Current state is safe.\n");
        } else {
            printf("Current state is not safe. Exiting...\n");
            return 1;
        }

        // Release resources
        printf("Enter resources to release: ");
        int release[MAX_RESOURCES];
        for (int i = 0; i < num_resources; i++)
            scanf("%d", &release[i]);

        release_resources(process_id, release);
        printf("Resources released successfully.\n");

        // Check if the current state is safe after releasing
        if (is_safe()) {
            printf("Current state is safe.\n");
        } else {
            printf("Current state is not safe. Exiting...\n");
            return 1;
        }
    }

    return 0;
}

// Initialize data structures
void initialize() {
    printf("Enter number of processes: ");
    scanf("%d", &num_processes);
    printf("Enter number of resources: ");
    scanf("%d", &num_resources);

    // Initialize available resources
    printf("Enter available resources: ");
    for (int i = 0; i < num_resources; i++)
        scanf("%d", &available[i]);

    // Initialize maximum resource matrix
    printf("Enter maximum resources for each process:\n");
    for (int i = 0; i < num_processes; i++) {
        printf("Process %d: ", i);
        for (int j = 0; j < num_resources; j++)
            scanf("%d", &maximum[i][j]);
    }

    // Initialize allocation and need matrices
    for (int i = 0; i < num_processes; i++) {
        for (int j = 0; j < num_resources; j++) {
            allocation[i][j] = 0;
            need[i][j] = maximum[i][j];
        }
    }
}

// Input current allocation and maximum needs
void input() {
    printf("Enter current allocation of resources for each process:\n");
    for (int i = 0; i < num_processes; i++) {
        printf("Process %d: ", i);
        for (int j = 0; j < num_resources; j++) {
            scanf("%d", &allocation[i][j]);
            need[i][j] = maximum[i][j] - allocation[i][j];
        }
    }
}

// Attempt to allocate resources to a process
bool request_resources(int process_id, int request[]) {
    // Check if request exceeds need
    for (int i = 0; i < num_resources; i++) {
        if (request[i] > need[process_id][i]) {
            printf("Request exceeds need. Allocation failed.\n");
            return false;
        }
        if (request[i] > available[i]) {
            printf("Insufficient available resources. Allocation failed.\n");
            return false;
        }
    }

    // Try to allocate resources
    for (int i = 0; i < num_resources; i++) {
        available[i] -= request[i];
        allocation[process_id][i] += request[i];
        need[process_id][i] -= request[i];
    }

    return true;
}

// Release resources allocated to a process
void release_resources(int process_id, int release[]) {
    for (int i = 0; i < num_resources; i++) {
        available[i] += release[i];
        allocation[process_id][i] -= release[i];
        need[process_id][i] += release[i];
    }
}

// Check if the current state is safe
bool is_safe() {
    bool finish[num_processes];
    int work[num_resources];
    int temp_allocation[num_processes][num_resources];

    // Initialize finish array
    for (int i = 0; i < num_processes; i++)
        finish[i] = false;

    // Initialize work array
    for (int i = 0; i < num_resources; i++)
        work[i] = available[i];

    // Make a temporary copy of allocation matrix
    for (int i = 0; i < num_processes; i++) {
        for (int j = 0; j < num_resources; j++) {
            temp_allocation[i][j] = allocation[i][j];
        }
    }

    // Find a process that can finish
    int count = 0;
    while (count < num_processes) {
        bool found = false;
        for (int i = 0; i < num_processes; i++) {
            if (!finish[i]) {
                bool can_finish = true;
                for (int j = 0; j < num_resources; j++) {
                    if (need[i][j] > work[j]) {
                        can_finish = false;
                        break;
                    }
                }
                if (can_finish) {
                    found = true;
                    finish[i] = true;
                    for (int j = 0; j < num_resources; j++)
                        work[j] += temp_allocation[i][j];
                    count++;
                }
            }
        }
        if (!found)
            break;
    }

    // If all processes are finished, the system is in a safe state
    for (int i = 0; i < num_processes; i++) {
        if (!finish[i])
            return false;
    }
    return true;
}
