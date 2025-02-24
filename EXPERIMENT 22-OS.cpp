#include <stdio.h>

#define MAX_MEMORY 1000

int memory[MAX_MEMORY];

// Function to initialize memory
void initializeMemory() {
    for (int i = 0; i < MAX_MEMORY; i++) {
        memory[i] = -1; // -1 indicates that the memory is unallocated
    }
}

// Function to display memory status
void displayMemory() {
    printf("\nMemory Status:\n");
    int i = 0;
    int foundFreeBlock = 0;

    while (i < MAX_MEMORY) {
        if (memory[i] == -1) {
            int start = i;
            while (i < MAX_MEMORY && memory[i] == -1) {
                i++;
            }
            printf("Free memory block %d-%d\n", start, i - 1);
            foundFreeBlock = 1;
        } else {
            i++;
        }
    }

    if (!foundFreeBlock) {
        printf("No free memory available.\n");
    }
}

// Function to allocate memory using best-fit algorithm
void allocateMemory(int processId, int size) {
    int bestStart = -1, bestSize = MAX_MEMORY;
    int start = -1, blockSize = 0;

    for (int i = 0; i <= MAX_MEMORY; i++) { 
        if (i < MAX_MEMORY && memory[i] == -1) {
            if (blockSize == 0) {
                start = i;
            }
            blockSize++;
        } else { 
            if (blockSize >= size && blockSize < bestSize) {  
                bestSize = blockSize;
                bestStart = start;
            }
            blockSize = 0;  
        }
    }

    if (bestStart != -1 && bestSize >= size) {
        for (int i = bestStart; i < bestStart + size; i++) {
            memory[i] = processId;
        }
        printf("\nAllocated memory block %d-%d to Process %d\n", bestStart, bestStart + size - 1, processId);
    } else {
        printf("\nMemory allocation for Process %d failed (not enough contiguous memory).\n", processId);
    }
}

// Function to deallocate memory
void deallocateMemory(int processId) {
    int released = 0;
    for (int i = 0; i < MAX_MEMORY; i++) {
        if (memory[i] == processId) {
            memory[i] = -1;
            released = 1;
        }
    }
    if (released) {
        printf("\nMemory released by Process %d\n", processId);
    } else {
        printf("\nNo memory found for Process %d\n", processId);
    }
}

// Main function to test the memory allocation
int main() {
    initializeMemory();
    displayMemory();

    allocateMemory(1, 200);
    displayMemory();

    allocateMemory(2, 300);
    displayMemory();

    deallocateMemory(1);
    displayMemory();

    allocateMemory(3, 400);
    displayMemory();

    return 0;
}
