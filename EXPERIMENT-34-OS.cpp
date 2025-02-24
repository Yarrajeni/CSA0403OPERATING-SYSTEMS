#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "sequential_file.txt"

// Structure to represent a record
struct Record {
    int recordNumber;
    char data[256]; // Adjust the size as needed for your records
};

int main() {
    FILE *file;
    struct Record record;
    int recordNumber;

    // Open file for writing
    file = fopen(FILENAME, "wb"); // Use "wb" for binary mode
    if (file == NULL) {
        printf("Error opening the file for writing.\n");
        return 1;
    }

    // Writing records to file
    printf("Enter records (Enter '0' as record number to exit):\n");
    while (1) {
        printf("Record Number: ");
        scanf("%d", &record.recordNumber);
        getchar(); // Consume the newline left by scanf

        if (record.recordNumber == 0) {
            break;
        }

        printf("Data: ");
        fgets(record.data, sizeof(record.data), stdin);

        // Remove trailing newline from fgets
        size_t len = strlen(record.data);
        if (len > 0 && record.data[len - 1] == '\n') {
            record.data[len - 1] = '\0';
        }

        // Write record to file
        fwrite(&record, sizeof(struct Record), 1, file);
    }
    fclose(file);

    // Reopen file for reading
    file = fopen(FILENAME, "rb");
    if (file == NULL) {
        printf("Error opening the file for reading.\n");
        return 1;
    }

    // Reading records
    while (1) {
        printf("Enter the record number to read (0 to exit): ");
        scanf("%d", &recordNumber);

        if (recordNumber == 0) {
            break;
        }

        // Seek to the correct record position
        fseek(file, (recordNumber - 1) * sizeof(struct Record), SEEK_SET);

        // Read and display the record
        if (fread(&record, sizeof(struct Record), 1, file)) {
            printf("\nRecord Number: %d\n", record.recordNumber);
            printf("Data: %s\n\n", record.data);
        } else {
            printf("Record not found.\n\n");
        }
    }

    fclose(file);
    return 0;
}
