#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024  // Define max line length

void searchFile(const char *pattern, const char *filename) {
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        perror("Error opening file");
        exit(1);
    }

    char line[MAX_LINE_LENGTH];

    while (fgets(line, sizeof(line), file)) {
        // Remove newline character at the end if it exists
        line[strcspn(line, "\n")] = '\0';

        if (strstr(line, pattern) != NULL) {
            printf("%s\n", line);
        }
    }

    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <pattern> <filename>\n", argv[0]);
        return 1;
    }

    const char *pattern = argv[1];
    const char *filename = argv[2];

    searchFile(pattern, filename);

    return 0;
}

