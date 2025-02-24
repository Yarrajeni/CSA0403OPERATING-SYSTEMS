#include <stdio.h>
void preemptive_priority_scheduling(int n, int bt[], int priority[]) {
    int wt[n], tat[n], remaining_bt[n], total_wt = 0, total_tat = 0;
    int completed = 0, time = 0;

    // Initialize remaining burst times
    for (int i = 0; i < n; i++) {
        remaining_bt[i] = bt[i];
    }

    while (completed < n) {
        int highest_priority = -1, highest_index = -1;

        // Find the process with the highest priority (smallest priority value)
        for (int i = 0; i < n; i++) {
            if (remaining_bt[i] > 0 && (highest_priority == -1 || priority[i] < highest_priority)) {
                highest_priority = priority[i];
                highest_index = i;
            }
        }

        // Execute the process with the highest priority
        remaining_bt[highest_index]--;
        time++;

        // If the process is completed
        if (remaining_bt[highest_index] == 0) {
            completed++;
            tat[highest_index] = time;
            wt[highest_index] = tat[highest_index] - bt[highest_index];
            total_wt += wt[highest_index];
            total_tat += tat[highest_index];
        }
    }

    // Display the results
    printf("P\tBT\tPriority\tWT\tTAT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t\t%d\t%d\n", i + 1, bt[i], priority[i], wt[i], tat[i]);
    }

    printf("Average Waiting Time: %.2f\n", (float)total_wt / n);
    printf("Average Turnaround Time: %.2f\n", (float)total_tat / n);
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int bt[n], priority[n];
    printf("Enter burst times:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &bt[i]);
    }

    printf("Enter priorities (lower value indicates higher priority):\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &priority[i]);
    }

    preemptive_priority_scheduling(n, bt, priority);
    return 0;
}
