#include <stdio.h>
#include <string.h>

#define MAX_FILES 10
#define FILENAME_LENGTH 100

struct Directory {
    char files[MAX_FILES][FILENAME_LENGTH];
    int fileCount;
};

void addFile(struct Directory *dir, const char *filename) {
    if (dir->fileCount < MAX_FILES) {
        strcpy(dir->files[dir->fileCount++], filename);
        printf("File '%s' added.\n", filename);
    } else {
        printf("Directory full.\n");
    }
}

void listFiles(struct Directory *dir) {
    for (int i = 0; i < dir->fileCount; i++) {
        printf("%s\n", dir->files[i]);
    }
}

void deleteFile(struct Directory *dir, const char *filename) {
    for (int i = 0; i < dir->fileCount; i++) {
        if (strcmp(dir->files[i], filename) == 0) {
            for (int j = i; j < dir->fileCount - 1; j++) {
                strcpy(dir->files[j], dir->files[j + 1]);
            }
            dir->fileCount--;
            printf("File '%s' deleted.\n", filename);
            return;
        }
    }
    printf("File not found.\n");
}

void searchFile(struct Directory *dir, const char *filename) {
    for (int i = 0; i < dir->fileCount; i++) {
        if (strcmp(dir->files[i], filename) == 0) {
            printf("File '%s' found.\n", filename);
            return;
        }
    }
    printf("File not found.\n");
}

int main() {
    struct Directory dir = {{}, 0};
    int choice;
    char filename[FILENAME_LENGTH];

    while (1) {
        printf("\n1. Add File\n2. List Files\n3. Delete File\n4. Search File\n5. Exit\nEnter choice: ");
        scanf("%d", &choice);
        getchar(); // to consume newline

        switch (choice) {
            case 1: 
                printf("Enter file name: ");
                fgets(filename, FILENAME_LENGTH, stdin);
                filename[strcspn(filename, "\n")] = '\0'; // Remove newline
                addFile(&dir, filename); break;
            case 2: listFiles(&dir); break;
            case 3:
                printf("Enter file name to delete: ");
                fgets(filename, FILENAME_LENGTH, stdin);
                filename[strcspn(filename, "\n")] = '\0';
                deleteFile(&dir, filename); break;
            case 4:
                printf("Enter file name to search: ");
                fgets(filename, FILENAME_LENGTH, stdin);
                filename[strcspn(filename, "\n")] = '\0';
                searchFile(&dir, filename); break;
            case 5: return 0;
            default: printf("Invalid choice.\n");
        }
    }
}
