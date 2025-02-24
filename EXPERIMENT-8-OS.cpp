#include <stdio.h>

void round_robin(int n, int bt[], int quantum) {
    int wt[n], tat[n], remaining_bt[n];
    int total_wt = 0, total_tat = 0, time = 0;

    // Copy burst times to remaining_bt array
    for (int i = 0; i < n; i++) {
        remaining_bt[i] = bt[i];
    }

    while (1) {
        int completed = 0;

        // Traverse all processes
        for (int i = 0; i < n; i++) {
            if (remaining_bt[i] > 0) {
                completed = 1;
                
                // If the remaining burst time of the process is greater than quantum
                if (remaining_bt[i] > quantum) {
                    time += quantum;
                    remaining_bt[i] -= quantum;
                }
                // If the remaining burst time of the process is less than or equal to quantum
                else {
                    time += remaining_bt[i];
                    wt[i] = time - bt[i];  // Waiting time is calculated after completion
                    tat[i] = time;         // Turnaround time is the time when it completes
                    total_wt += wt[i];
                    total_tat += tat[i];
                    remaining_bt[i] = 0;   // Process is completed
                }
            }
        }

        // If all processes are completed, exit the loop
        if (completed == 0)
            break;
    }

    // Display the results
    printf("P\tBT\tWT\tTAT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\n", i + 1, bt[i], wt[i], tat[i]);
    }

    // Display average waiting time and turnaround time
    printf("Average Waiting Time: %.2f\n", (float)total_wt / n);
    printf("Average Turnaround Time: %.2f\n", (float)total_tat / n);
}

int main() {
    int n, quantum;

    // Take input for number of processes
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int bt[n];
    printf("Enter burst times:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &bt[i]);
    }

    // Take input for time quantum
    printf("Enter time quantum: ");
    scanf("%d", &quantum);

    // Call round robin function to simulate the algorithm
    round_robin(n, bt, quantum);

    return 0;
}
