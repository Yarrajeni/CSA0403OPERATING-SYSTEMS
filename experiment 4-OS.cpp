#include <stdio.h>

void schedule(int n, int bt[]) {
    int wt[n], tat[n], total_wt = 0, total_tat = 0, time = 0;

    while (1) {
        int min_burst = -1, min_index = -1;
        for (int i = 0; i < n; i++) {
            if (bt[i] > 0 && (min_burst == -1 || bt[i] < min_burst)) {
                min_burst = bt[i];
                min_index = i;
            }
        }

        if (min_index == -1) break;

        wt[min_index] = time;
        time += bt[min_index];
        tat[min_index] = time;
        total_wt += wt[min_index];
        total_tat += tat[min_index];
        bt[min_index] = 0;  // Process completed
    }

    printf("P\tBT\tWT\tTAT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\n", i + 1, bt[i], wt[i], tat[i]);
    }
    printf("Avg WT: %.2f, Avg TAT: %.2f\n", (float)total_wt / n, (float)total_tat / n);
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

    schedule(n, bt);
    return 0;
}
