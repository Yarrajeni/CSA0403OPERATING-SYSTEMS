#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid;

    // Create a new process
    pid = fork();

    if (pid < 0) {
        // Fork failed
        perror("Fork failed");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Child process
        char *args[] = {NULL}; // No arguments for exec
        execvp("echo", args); // Replace child process with echo command
        perror("Exec failed"); // If exec fails
        exit(EXIT_FAILURE);
    } else {
        // Parent process
        printf("Parent Process ID: %d\n", getpid());
        printf("Created Child Process ID: %d\n", pid);
    }

    return 0;
}
