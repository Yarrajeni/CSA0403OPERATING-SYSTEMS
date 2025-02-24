#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>  // Include for wait() function

// Define message structure
#define MAX_TEXT 512

struct message {
    long msg_type;       // Message type (must be > 0)
    char msg_text[MAX_TEXT];  // Message content
};

int main() {
    key_t key = 1234;  // Key for the message queue
    int msg_id;
    struct message msg;
    pid_t pid;

    // Create message queue
    msg_id = msgget(key, 0666 | IPC_CREAT);
    if (msg_id < 0) {
        perror("msgget failed");
        exit(1);
    } else {
        printf("Shared memory (Message Queue) created with ID: %d\n", msg_id);
    }

    pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    }

    if (pid == 0) {  // Child Process
        // Receive message from message queue
        printf("Child: Waiting to receive message...\n");

        // Ensure the message size in msgrcv() is the size of the structure minus the type field
        if (msgrcv(msg_id, &msg, sizeof(msg.msg_text), 0, 0) == -1) {
            perror("msgrcv failed");
            exit(1);
        }

        // Print received message
        printf("Child: Received message: %s\n", msg.msg_text);

        // Child does not remove the message queue, it's the parent process's responsibility

    } else {  // Parent Process
        // Send message to message queue
        msg.msg_type = 1;  // Message type must be positive
        strcpy(msg.msg_text, "Hello from Parent Process!");

        if (msgsnd(msg_id, &msg, sizeof(msg.msg_text), 0) == -1) {
            perror("msgsnd failed");
            exit(1);
        }

        printf("Parent: Message sent.\n");

        // Wait for child to read the message
        wait(NULL);

        // Parent removes the message queue after the child has finished
        if (msgctl(msg_id, IPC_RMID, NULL) == -1) {
            perror("msgctl failed");
            exit(1);
        }
        printf("Parent: Message queue removed.\n");
    }

    return 0;
}
