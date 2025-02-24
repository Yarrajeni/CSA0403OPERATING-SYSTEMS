#include <stdio.h>
#include <stdlib.h>

#define MAX_BLOCKS 5

struct MemoryBlock {
    int size;
    int free;
};

int firstFit(struct MemoryBlock blocks[], int blockCount, int size) {
    for (int i = 0; i < blockCount; i++) {
        if (blocks[i].free && blocks[i].size >= size) {
            blocks[i].free = 0;
            printf("Allocated %d units at block %d (First-Fit).\n", size, i);
            return i;
        }
    }
    printf("No block for %d units (First-Fit).\n", size);
    return -1;
}

int bestFit(struct MemoryBlock blocks[], int blockCount, int size) {
    int bestIndex = -1, minDiff = __INT_MAX__;
    for (int i = 0; i < blockCount; i++) {
        if (blocks[i].free && blocks[i].size >= size) {
            int diff = blocks[i].size - size;
            if (diff < minDiff) { minDiff = diff; bestIndex = i; }
        }
    }
    if (bestIndex != -1) {
        blocks[bestIndex].free = 0;
        printf("Allocated %d units at block %d (Best-Fit).\n", size, bestIndex);
    }
    return bestIndex;
}

int worstFit(struct MemoryBlock blocks[], int blockCount, int size) {
    int worstIndex = -1, maxDiff = -1;
    for (int i = 0; i < blockCount; i++) {
        if (blocks[i].free && blocks[i].size >= size) {
            int diff = blocks[i].size - size;
            if (diff > maxDiff) { maxDiff = diff; worstIndex = i; }
        }
    }
    if (worstIndex != -1) {
        blocks[worstIndex].free = 0;
        printf("Allocated %d units at block %d (Worst-Fit).\n", size, worstIndex);
    }
    return worstIndex;
}

void deallocate(struct MemoryBlock blocks[], int index) {
    if (index != -1) {
        blocks[index].free = 1;
        printf("Deallocated block %d.\n", index);
    }
}

void displayMemoryBlocks(struct MemoryBlock blocks[], int blockCount) {
    for (int i = 0; i < blockCount; i++) {
        printf("Block %d: Size = %d, %s\n", i, blocks[i].size, blocks[i].free ? "Free" : "Allocated");
    }
}

int main() {
    struct MemoryBlock blocks[MAX_BLOCKS] = {
        {100, 1}, {200, 1}, {300, 1}, {400, 1}, {500, 1}
    };

    int choice, size, blockIndex;
    while (1) {
        printf("\n1. First-Fit Allocation\n2. Best-Fit Allocation\n3. Worst-Fit Allocation\n4. Deallocate Memory\n5. Display Memory\n6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: printf("Enter size: "); scanf("%d", &size); firstFit(blocks, MAX_BLOCKS, size); break;
            case 2: printf("Enter size: "); scanf("%d", &size); bestFit(blocks, MAX_BLOCKS, size); break;
            case 3: printf("Enter size: "); scanf("%d", &size); worstFit(blocks, MAX_BLOCKS, size); break;
            case 4: printf("Enter block index to deallocate: "); scanf("%d", &blockIndex); deallocate(blocks, blockIndex); break;
            case 5: displayMemoryBlocks(blocks, MAX_BLOCKS); break;
            case 6: exit(0);
            default: printf("Invalid choice!\n");
        }
    }
    return 0;
}
