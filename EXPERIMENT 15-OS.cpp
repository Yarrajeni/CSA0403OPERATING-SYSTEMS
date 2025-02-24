#include <stdio.h>
#include <string.h>

#define MAX_DIRS 5
#define MAX_FILES 5
#define FILENAME_LENGTH 100
#define DIRNAME_LENGTH 50

struct File {
    char filename[FILENAME_LENGTH];
};

struct Directory {
    char dirname[DIRNAME_LENGTH];
    struct File files[MAX_FILES];
    int fileCount;
};

struct MainDirectory {
    struct Directory dirs[MAX_DIRS];
    int dirCount;
};

void addDirectory(struct MainDirectory *mainDir, const char *dirname) {
    if (mainDir->dirCount < MAX_DIRS) {
        strcpy(mainDir->dirs[mainDir->dirCount++].dirname, dirname);
        printf("Directory '%s' added.\n", dirname);
    }
}

void addFile(struct MainDirectory *mainDir, const char *dirname, const char *filename) {
    for (int i = 0; i < mainDir->dirCount; i++) {
        if (strcmp(mainDir->dirs[i].dirname, dirname) == 0 && mainDir->dirs[i].fileCount < MAX_FILES) {
            strcpy(mainDir->dirs[i].files[mainDir->dirs[i].fileCount++].filename, filename);
            printf("File '%s' added to '%s'.\n", filename, dirname);
            return;
        }
    }
    printf("Directory or file limit exceeded.\n");
}

void listDirectories(struct MainDirectory *mainDir) {
    for (int i = 0; i < mainDir->dirCount; i++) {
        printf("Directory '%s':\n", mainDir->dirs[i].dirname);
        for (int j = 0; j < mainDir->dirs[i].fileCount; j++) {
            printf("  %s\n", mainDir->dirs[i].files[j].filename);
        }
    }
}

int main() {
    struct MainDirectory mainDir = {{}, 0};
    int choice;
    char dirname[DIRNAME_LENGTH], filename[FILENAME_LENGTH];

    while (1) {
        printf("\n1. Add Directory\n2. Add File\n3. List Directories\n4. Exit\nChoice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                printf("Enter directory name: ");
                fgets(dirname, DIRNAME_LENGTH, stdin);
                dirname[strcspn(dirname, "\n")] = '\0';
                addDirectory(&mainDir, dirname);
                break;
            case 2:
                printf("Enter directory name: ");
                fgets(dirname, DIRNAME_LENGTH, stdin);
                dirname[strcspn(dirname, "\n")] = '\0';
                printf("Enter file name: ");
                fgets(filename, FILENAME_LENGTH, stdin);
                filename[strcspn(filename, "\n")] = '\0';
                addFile(&mainDir, dirname, filename);
                break;
            case 3:
                listDirectories(&mainDir);
                break;
            case 4:
                return 0;
            default:
                printf("Invalid choice.\n");
        }
    }

    return 0;
}
