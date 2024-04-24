import java.util.*;

class Process {
    int id;
    int arrivalTime;
    int burstTime;
    int priority;
}

public class QuestionOne {

    static class ArrivalTimeComparator implements Comparator<Process> {
        public int compare(Process a, Process b) {
            return Integer.compare(a.arrivalTime, b.arrivalTime);
        }
    }

    static class BurstTimeComparator implements Comparator<Process> {
        public int compare(Process a, Process b) {
            return Integer.compare(a.burstTime, b.burstTime);
        }
    }

    static class PriorityComparator implements Comparator<Process> {
        public int compare(Process a, Process b) {
            return Integer.compare(a.priority, b.priority);
        }
    }

    static void calculateTurnaroundTimeAndWaitingTime(List<Process> processes, int[] turnaroundTime, int[] waitingTime) {
        int n = processes.size();
        waitingTime[0] = 0;
        turnaroundTime[0] = processes.get(0).burstTime;

        for (int i = 1; i < n; ++i) {
            waitingTime[i] = waitingTime[i - 1] + processes.get(i - 1).burstTime;
            turnaroundTime[i] = waitingTime[i] + processes.get(i).burstTime;
        }
    }

    static void printResults(List<Process> processes, int[] turnaroundTime, int[] waitingTime) {
        System.out.println("Process\tTurnaround Time\tWaiting Time");
        for (int i = 0; i < processes.size(); ++i) {
            System.out.println(processes.get(i).id + "\t" + turnaroundTime[i] + "\t\t\t" + waitingTime[i]);
        }
    }

    static void FCFS(List<Process> processes) {
        processes.sort(new ArrivalTimeComparator());
        int[] turnaroundTime = new int[processes.size()];
        int[] waitingTime = new int[processes.size()];
        calculateTurnaroundTimeAndWaitingTime(processes, turnaroundTime, waitingTime);
        printResults(processes, turnaroundTime, waitingTime);
    }

    static void SJF(List<Process> processes) {
        processes.sort(new BurstTimeComparator());
        int[] turnaroundTime = new int[processes.size()];
        int[] waitingTime = new int[processes.size()];
        calculateTurnaroundTimeAndWaitingTime(processes, turnaroundTime, waitingTime);
        printResults(processes, turnaroundTime, waitingTime);
    }

    static void Priority(List<Process> processes) {
        processes.sort(new PriorityComparator());
        int[] turnaroundTime = new int[processes.size()];
        int[] waitingTime = new int[processes.size()];
        calculateTurnaroundTimeAndWaitingTime(processes, turnaroundTime, waitingTime);
        printResults(processes, turnaroundTime, waitingTime);
    }

    static void RoundRobin(List<Process> processes, int quantum) {
        int n = processes.size();
        int[] remainingTime = new int[n];
        int[] turnaroundTime = new int[n];
        int[] waitingTime = new int[n];

        for (int i = 0; i < n; ++i) {
            remainingTime[i] = processes.get(i).burstTime;
        }

        int currentTime = 0;
        while (true) {
            boolean done = true;
            for (int i = 0; i < n; ++i) {
                if (remainingTime[i] > 0) {
                    done = false;
                    if (remainingTime[i] > quantum) {
                        currentTime += quantum;
                        remainingTime[i] -= quantum;
                    } else {
                        currentTime += remainingTime[i];
                        waitingTime[i] = currentTime - processes.get(i).burstTime;
                        remainingTime[i] = 0;
                    }
                }
            }
            if (done) break;
        }

        for (int i = 0; i < n; ++i) {
            turnaroundTime[i] = processes.get(i).burstTime + waitingTime[i];
        }

        printResults(processes, turnaroundTime, waitingTime);
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter the number of processes: ");
        int n = scanner.nextInt();

        List<Process> processes = new ArrayList<>();
        System.out.println("Enter arrival time, burst time, and priority for each process:");
        for (int i = 0; i < n; ++i) {
            Process process = new Process();
            process.id = i + 1;
            System.out.println("Process " + (i + 1) + ":");
            System.out.print("Arrival Time: ");
            process.arrivalTime = scanner.nextInt();
            System.out.print("Burst Time: ");
            process.burstTime = scanner.nextInt();
            System.out.print("Priority: ");
            process.priority = scanner.nextInt();
            processes.add(process);
        }

        System.out.println("\nFCFS Scheduling:");
        FCFS(new ArrayList<>(processes));

        System.out.println("\nSJF Scheduling:");
        SJF(new ArrayList<>(processes));

        System.out.println("\nPriority Scheduling:");
        Priority(new ArrayList<>(processes));

        System.out.print("\nEnter time quantum for Round Robin: ");
        int quantum = scanner.nextInt();
        System.out.println("\nRound Robin Scheduling:");
        RoundRobin(new ArrayList<>(processes), quantum);

        scanner.close();
    }
}
