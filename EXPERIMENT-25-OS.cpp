#include <stdio.h>    // For printf(), perror()
#include <stdlib.h>   // For exit()
#include <fcntl.h>    // For open(), O_RDONLY, O_CREAT
#include <unistd.h>   // For close()
#include <errno.h>    // For errno

int main() {
    // Try to open the file for reading; if it doesn't exist, create it
    int fd = open("foo.txt", O_RDONLY | O_CREAT, 0644);  

    printf("fd = %d\n", fd);  // Print the file descriptor

    // Check if there was an error in opening the file
    if (fd == -1) {
        printf("Error Number: %d\n", errno);  // Print error number
        perror("Program");  // Print system error message
        exit(1);  // Exit the program with error status
    }

    close(fd);  // Close the file
    return 0;
}
