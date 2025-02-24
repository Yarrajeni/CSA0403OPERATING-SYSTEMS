#include <stdio.h>

void schedule(int n, int bt[], int priority[]) {
    int wt[n], tat[n], total_wt = 0, total_tat = 0, time = 0;

    while (1) {
        int highest_priority = -1, highest_index = -1;
        
        // Find the process with the highest priority (smallest priority value)
        for (int i = 0; i < n; i++) {
            if (priority[i] > 0 && (highest_priority == -1 || priority[i] < highest_priority)) {
                highest_priority = priority[i];
                highest_index = i;
            }
        }

        if (highest_index == -1) break;  // All processes are completed

        wt[highest_index] = time;
        time += bt[highest_index];
        tat[highest_index] = time;
        total_wt += wt[highest_index];
        total_tat += tat[highest_index];
        priority[highest_index] = 0;  // Process completed
    }

    printf("P\tBT\tPriority\tWT\tTAT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t\t%d\t%d\n", i + 1, bt[i], priority[i], wt[i], tat[i]);
    }
    printf("Avg WT: %.2f, Avg TAT: %.2f\n", (float)total_wt / n, (float)total_tat / n);
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

    printf("Enter priorities:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &priority[i]);
    }

    schedule(n, bt, priority);
    return 0;
}
