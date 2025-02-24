#include <stdio.h>

void non_preemptive_sjf(int n, int bt[]) {
    int wt[n], tat[n], total_wt = 0, total_tat = 0;
    int completed = 0, time = 0;
    int bt_copy[n];

    // Copy burst times to bt_copy to keep original burst times intact
    for (int i = 0; i < n; i++) {
        bt_copy[i] = bt[i];
    }

    // Sort the processes based on burst times (SJF)
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (bt_copy[i] > bt_copy[j]) {
                int temp = bt_copy[i];
                bt_copy[i] = bt_copy[j];
                bt_copy[j] = temp;
            }
        }
    }

    // Calculate waiting time and turnaround time
    while (completed < n) {
        int min_bt_index = -1;
        
        // Find the process with the shortest burst time that hasn't been completed
        for (int i = 0; i < n; i++) {
            if (bt_copy[i] > 0 && (min_bt_index == -1 || bt_copy[i] < bt_copy[min_bt_index])) {
                min_bt_index = i;
            }
        }

        // Execute the process with the smallest burst time
        wt[min_bt_index] = time;
        time += bt[min_bt_index];
        tat[min_bt_index] = time;
        total_wt += wt[min_bt_index];
        total_tat += tat[min_bt_index];
        bt_copy[min_bt_index] = 0; // Process completed
        completed++;
    }

    // Print the results
    printf("P\tBT\tWT\tTAT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\n", i + 1, bt[i], wt[i], tat[i]);
    }

    // Calculate average waiting time and turnaround time
    printf("Average Waiting Time: %.2f\n", (float)total_wt / n);
    printf("Average Turnaround Time: %.2f\n", (float)total_tat / n);
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int bt[n];
    printf("Enter burst times:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &bt[i]);
    }

    non_preemptive_sjf(n, bt);
    return 0;
}
