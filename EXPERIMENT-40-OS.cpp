#include <stdio.h>
#include <sys/stat.h>  // Required for chmod()
#include <sys/types.h> // Defines mode_t

int main() {
    char filename[] = "file.txt";

    // New permissions: rw-rw-r--
    mode_t new_permissions = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH;

    // Change file permissions
    if (chmod(filename, new_permissions) == 0) {
        printf("File permissions changed successfully.\n");
    } else {
        perror("chmod"); // Print error if failed
        return 1;
    }

    return 0;
}
