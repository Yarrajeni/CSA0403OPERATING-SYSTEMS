#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to represent a block
struct Block {
    char data[256]; // Data storage for the block
    struct Block* next; // Pointer to the next block
};

int main() {
    struct Block* firstBlock = NULL; // Pointer to the first block
    struct Block* lastBlock = NULL; // Pointer to the last block
    int blockCount = 0; // Keeps track of the total number of blocks
    int blockNumber;
    char data[256]; 
    char choice;

    printf("Linked Allocation Simulation\n");

    while (1) {
        printf("\nEnter 'W' to write a block, 'R' to read a block, or 'Q' to quit: ");
        scanf(" %c", &choice);
        getchar(); // Handle newline character

        if (choice == 'Q' || choice == 'q') {
            break;
        }

        if (choice == 'W' || choice == 'w') {
            printf("Enter data for the block: ");
            fgets(data, sizeof(data), stdin);
            
            // Remove newline character from fgets
            size_t len = strlen(data);
            if (len > 0 && data[len - 1] == '\n') {
                data[len - 1] = '\0';
            }

            // Allocate memory for new block
            struct Block* newBlock = (struct Block*)malloc(sizeof(struct Block));
            if (newBlock == NULL) {
                printf("Memory allocation failed.\n");
                return 1;
            }

            strcpy(newBlock->data, data);
            newBlock->next = NULL;

            if (blockCount == 0) {
                // First block
                firstBlock = newBlock;
                lastBlock = newBlock;
            } else {
                // Link the new block
                lastBlock->next = newBlock;
                lastBlock = newBlock;
            }

            blockCount++;
            printf("Block %d written successfully.\n", blockCount);
        } 
        else if (choice == 'R' || choice == 'r') {
            printf("Enter the block number to read (1-%d): ", blockCount);
            scanf("%d", &blockNumber);

            if (blockNumber < 1 || blockNumber > blockCount) {
                printf("Invalid block number. The valid range is 1-%d.\n", blockCount);
            } 
            else {
                struct Block* currentBlock = firstBlock;
                for (int i = 1; i < blockNumber; i++) {
                    currentBlock = currentBlock->next;
                }
                printf("Block %d Data: %s\n", blockNumber, currentBlock->data);
            }
        } 
        else {
            printf("Invalid choice! Please enter 'W', 'R', or 'Q'.\n");
        }
    }

    // Free allocated memory before exiting
    struct Block* currentBlock = firstBlock;
    while (currentBlock != NULL) {
        struct Block* nextBlock = currentBlock->next;
        free(currentBlock);
        currentBlock = nextBlock;
    }

    printf("Program exited successfully.\n");
    return 0;
}
