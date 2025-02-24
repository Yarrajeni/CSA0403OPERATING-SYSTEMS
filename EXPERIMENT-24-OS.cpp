#include <stdio.h>     // For printf(), perror()
#include <stdlib.h>    // For exit()
#include <fcntl.h>     // For open(), O_WRONLY, O_APPEND, O_CREAT
#include <unistd.h>    // For write(), read(), close(), remove()
#include <sys/stat.h>  // For file permission macros like S_IRWXU
#include <string.h>    // For strlen()

int main() {  
    int fd;  
    char buffer[100];  

    // Creating a new file  
    fd = open("sample.txt", O_CREAT | O_WRONLY, S_IRWXU);  
    if (fd == -1) {  
        perror("create");  
        exit(1);  
    } else {  
        printf("File 'sample.txt' created successfully.\n");  
        close(fd);  
    }  

    // Opening an existing file for writing  
    fd = open("sample.txt", O_WRONLY | O_APPEND);  
    if (fd == -1) {  
        perror("open");  
        exit(1);  
    } else {  
        printf("File 'sample.txt' opened for writing.\n");  
    }  

    // Writing data to the file  
    const char *data = "Hello, World!\n";
    if (write(fd, data, strlen(data)) == -1) {  
        perror("write");  
        exit(1);  
    }  
    printf("Data written to 'sample.txt'.\n");  
    close(fd);  

    // Opening the file for reading  
    fd = open("sample.txt", O_RDONLY);  
    if (fd == -1) {  
        perror("open");  
        exit(1);  
    } else {  
        printf("File 'sample.txt' opened for reading.\n");  
    }  

    // Reading data from the file  
    int bytesRead = read(fd, buffer, sizeof(buffer) - 1);  // Leave space for null terminator  
    if (bytesRead == -1) {  
        perror("read");  
        exit(1);  
    } else {  
        buffer[bytesRead] = '\0';  // Null-terminate the string  
        printf("Data read from 'sample.txt':\n%s\n", buffer);  
    }  
    close(fd);  

    // Deleting the file  
    if (remove("sample.txt") == -1) {  
        perror("remove");  
        exit(1);  
    } else {  
        printf("File 'sample.txt' deleted.\n");  
    }  

    return 0;  
}  
