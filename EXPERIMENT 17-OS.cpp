#include <stdio.h>
#include <stdbool.h>

#define MAX_PROC 5
#define MAX_RES 3

// Function to check if the system is in a safe state
bool isSafeState(int processes, int resources, int alloc[processes][resources], int max[processes][resources], int avail[resources]) {
    int work[resources], finish[processes];

    // Initialize work array with available resources
    for (int i = 0; i < resources; i++) {
        work[i] = avail[i];
    }

    // Initialize finish array to 0 (not finished)
    for (int i = 0; i < processes; i++) {
        finish[i] = 0;
    }

    int safeCount = 0;
    while (safeCount < processes) {
        bool progress = false;
        for (int i = 0; i < processes; i++) {
            if (!finish[i]) {
                bool canFinish = true;
                for (int j = 0; j < resources; j++) {
                    if (max[i][j] - alloc[i][j] > work[j]) {
                        canFinish = false;
                        break;
                    }
                }

                if (canFinish) {
                    for (int j = 0; j < resources; j++) {
                        work[j] += alloc[i][j]; // Add allocated resources back to work
                    }
                    finish[i] = 1; // Mark this process as finished
                    safeCount++;
                    progress = true;
                    break;
                }
            }
        }

        if (!progress) {
            // If no process can finish, system is unsafe
            return false;
        }
    }
    return true;
}

// Function to request resources for a process and check safety
void requestResources(int processes, int resources, int alloc[processes][resources], int max[processes][resources], int avail[resources], int p, int req[resources]) {
    // Check if request is valid
    for (int i = 0; i < resources; i++) {
        if (req[i] > max[p][i] - alloc[p][i]) {
            printf("Error: Process has exceeded its maximum claim.\n");
            return;
        }
        if (req[i] > avail[i]) {
            printf("Error: Not enough resources available.\n");
            return;
        }
    }

    // Temporarily allocate the resources
    for (int i = 0; i < resources; i++) {
        avail[i] -= req[i];
        alloc[p][i] += req[i];
    }

    // Check if the system remains in a safe state
    if (isSafeState(processes, resources, alloc, max, avail)) {
        printf("Resources allocated successfully.\n");
    } else {
        // Rollback if system is unsafe
        for (int i = 0; i < resources; i++) {
            avail[i] += req[i];
            alloc[p][i] -= req[i];
        }
        printf("Request would lead to deadlock. Rollback!\n");
    }
}

int main() {
    int processes = 5, resources = 3;
    int alloc[processes][resources] = {{0, 1, 0}, {2, 0, 0}, {3, 0, 2}, {2, 1, 1}, {0, 0, 2}};
    int max[processes][resources] = {{7, 5, 3}, {3, 2, 2}, {9, 0, 2}, {2, 2, 2}, {4, 3, 3}};
    int avail[resources] = {3, 3, 2};
    int req[resources];

    printf("Enter resource request for process 1 (in the form of resource counts):\n");
    for (int i = 0; i < resources; i++) {
        printf("Resource %d: ", i);
        scanf("%d", &req[i]);
    }

    // Request resources for process 1 (processNum = 1)
    requestResources(processes, resources, alloc, max, avail, 1, req);

    return 0;
}
