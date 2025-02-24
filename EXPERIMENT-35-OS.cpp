#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "indexed_file.txt"
#define INDEXFILE "index_file.txt"
#define MAX_BLOCKS 100 // Maximum blocks in index

// Structure to represent a block
struct Block {
    int blockNumber;
    char data[256]; // Adjust the size as needed
};

int main() {
    FILE *file, *indexFile;
    struct Block block;
    int blockNumber;
    int indexBlock[MAX_BLOCKS] = {-1}; // -1 means unused

    // Load existing index file if available
    indexFile = fopen(INDEXFILE, "rb");
    if (indexFile != NULL) {
        fread(indexBlock, sizeof(int), MAX_BLOCKS, indexFile);
        fclose(indexFile);
    }

    // Open file in append mode for writing blocks
    file = fopen(FILENAME, "ab");
    if (file == NULL) {
        printf("Error opening the file for writing.\n");
        return 1;
    }

    // Writing blocks
    printf("Enter blocks (Enter '0' as block number to exit):\n");
    while (1) {
        printf("Block Number: ");
        scanf("%d", &block.blockNumber);
        getchar(); // Consume newline after scanf

        if (block.blockNumber == 0) {
            break;
        }

        if (block.blockNumber >= MAX_BLOCKS) {
            printf("Block number exceeds maximum limit!\n");
            continue;
        }

        printf("Data: ");
        fgets(block.data, sizeof(block.data), stdin);
        
        // Remove newline from fgets
        size_t len = strlen(block.data);
        if (len > 0 && block.data[len - 1] == '\n') {
            block.data[len - 1] = '\0';
        }

        // Get current file position for indexing
        fseek(file, 0, SEEK_END);
        indexBlock[block.blockNumber] = ftell(file);

        // Write the block
        fwrite(&block, sizeof(struct Block), 1, file);
    }
    fclose(file);

    // Save index block to a separate file
    indexFile = fopen(INDEXFILE, "wb");
    if (indexFile == NULL) {
        printf("Error opening index file for writing.\n");
        return 1;
    }
    fwrite(indexBlock, sizeof(int), MAX_BLOCKS, indexFile);
    fclose(indexFile);

    // Reopen the file in read mode
    file = fopen(FILENAME, "rb");
    if (file == NULL) {
        printf("Error opening the file for reading.\n");
        return 1;
    }

    // Read blocks
    while (1) {
        printf("Enter the block number to read (0 to exit): ");
        scanf("%d", &blockNumber);

        if (blockNumber == 0) {
            break;
        }

        if (blockNumber >= MAX_BLOCKS || indexBlock[blockNumber] == -1) {
            printf("Block not found.\n");
            continue;
        }

        // Seek and read block
        fseek(file, indexBlock[blockNumber], SEEK_SET);
        fread(&block, sizeof(struct Block), 1, file);

        printf("\nBlock Number: %d\n", block.blockNumber);
        printf("Data: %s\n\n", block.data);
    }

    fclose(file);
    return 0;
}
