#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Process {
    int id;
    int arrivalTime;
    int burstTime;
    int priority;
};

bool compareArrivalTime(const Process& a, const Process& b) {
    return a.arrivalTime < b.arrivalTime;
}

bool compareBurstTime(const Process& a, const Process& b) {
    return a.burstTime < b.burstTime;
}

bool comparePriority(const Process& a, const Process& b) {
    return a.priority < b.priority;
}

void calculateTurnaroundTimeAndWaitingTime(vector<Process>& processes, vector<int>& turnaroundTime, vector<int>& waitingTime) {
    int n = processes.size();
    turnaroundTime.resize(n);
    waitingTime.resize(n);

    waitingTime[0] = 0;
    turnaroundTime[0] = processes[0].burstTime;

    for (int i = 1; i < n; ++i) {
        waitingTime[i] = waitingTime[i - 1] + processes[i - 1].burstTime;
        turnaroundTime[i] = waitingTime[i] + processes[i].burstTime;
    }
}

void printResults(const vector<Process>& processes, const vector<int>& turnaroundTime, const vector<int>& waitingTime) {
    cout << "Process\tTurnaround Time\tWaiting Time\n";
    for (size_t i = 0; i < processes.size(); ++i) {
        cout << processes[i].id << "\t" << turnaroundTime[i] << "\t\t\t" << waitingTime[i] << endl;
    }
}

void FCFS(vector<Process>& processes) {
    sort(processes.begin(), processes.end(), compareArrivalTime);
    vector<int> turnaroundTime, waitingTime;
    calculateTurnaroundTimeAndWaitingTime(processes, turnaroundTime, waitingTime);
    printResults(processes, turnaroundTime, waitingTime);
}

void SJF(vector<Process>& processes) {
    sort(processes.begin(), processes.end(), compareBurstTime);
    vector<int> turnaroundTime, waitingTime;
    calculateTurnaroundTimeAndWaitingTime(processes, turnaroundTime, waitingTime);
    printResults(processes, turnaroundTime, waitingTime);
}

void Priority(vector<Process>& processes) {
    sort(processes.begin(), processes.end(), comparePriority);
    vector<int> turnaroundTime, waitingTime;
    calculateTurnaroundTimeAndWaitingTime(processes, turnaroundTime, waitingTime);
    printResults(processes, turnaroundTime, waitingTime);
}

void RoundRobin(vector<Process>& processes, int quantum) {
    int n = processes.size();
    vector<int> remainingTime(n);
    vector<int> turnaroundTime(n);
    vector<int> waitingTime(n);

    for (int i = 0; i < n; ++i) {
        remainingTime[i] = processes[i].burstTime;
    }

    int currentTime = 0;
    while (true) {
        bool done = true;
        for (int i = 0; i < n; ++i) {
            if (remainingTime[i] > 0) {
                done = false;
                if (remainingTime[i] > quantum) {
                    currentTime += quantum;
                    remainingTime[i] -= quantum;
                } else {
                    currentTime += remainingTime[i];
                    waitingTime[i] = currentTime - processes[i].burstTime;
                    remainingTime[i] = 0;
                }
            }
        }
        if (done) break;
    }

    for (int i = 0; i < n; ++i) {
        turnaroundTime[i] = processes[i].burstTime + waitingTime[i];
    }

    printResults(processes, turnaroundTime, waitingTime);
}

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes(n);
    cout << "Enter arrival time, burst time, and priority for each process:\n";
    for (int i = 0; i < n; ++i) {
        processes[i].id = i + 1;
        cout << "Process " << i + 1 << ":\n";
        cout << "Arrival Time: ";
        cin >> processes[i].arrivalTime;
        cout << "Burst Time: ";
        cin >> processes[i].burstTime;
        cout << "Priority: ";
        cin >> processes[i].priority;
    }

    cout << "\nFCFS Scheduling:\n";
    FCFS(processes);

    cout << "\nSJF Scheduling:\n";
    SJF(processes);

    cout << "\nPriority Scheduling:\n";
    Priority(processes);

    int quantum;
    cout << "\nEnter time quantum for Round Robin: ";
    cin >> quantum;
    cout << "\nRound Robin Scheduling:\n";
    RoundRobin(processes, quantum);

    return 0;
}
