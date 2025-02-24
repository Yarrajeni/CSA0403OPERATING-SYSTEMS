#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, head, seek_time = 0;

    printf("Enter the number of disk requests: ");
    scanf("%d", &n);

    int request_queue[n];
    printf("Enter the disk request queue:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &request_queue[i]);
    }

    printf("Enter the initial position of the disk head: ");
    scanf("%d", &head);

    // Sorting requests for C-SCAN
    int left[n], right[n];  // Separate arrays for two sides
    int left_count = 0, right_count = 0;

    for (int i = 0; i < n; i++) {
        if (request_queue[i] < head) {
            left[left_count++] = request_queue[i];  // Requests less than head
        } else {
            right[right_count++] = request_queue[i]; // Requests greater than head
        }
    }

    // Sort both halves
    for (int i = 0; i < left_count - 1; i++) {
        for (int j = i + 1; j < left_count; j++) {
            if (left[i] > left[j]) {
                int temp = left[i];
                left[i] = left[j];
                left[j] = temp;
            }
        }
    }
    for (int i = 0; i < right_count - 1; i++) {
        for (int j = i + 1; j < right_count; j++) {
            if (right[i] > right[j]) {
                int temp = right[i];
                right[i] = right[j];
                right[j] = temp;
            }
        }
    }

    printf("\nC-SCAN Disk Scheduling:\n");

    // Move to right side requests
    for (int i = 0; i < right_count; i++) {
        seek_time += abs(head - right[i]);
        printf("Move to %d (Seek Time: %d)\n", right[i], seek_time);
        head = right[i];
    }

    // Move to max boundary (assuming max cylinder number is 199)
    seek_time += abs(head - 199);
    printf("Move to 199 (Seek Time: %d)\n", seek_time);
    head = 199;

    // Jump to the lowest request (circular movement)
    seek_time += abs(head - 0);
    printf("Move to 0 (Seek Time: %d)\n", seek_time);
    head = 0;

    // Move to left side requests
    for (int i = 0; i < left_count; i++) {
        seek_time += abs(head - left[i]);
        printf("Move to %d (Seek Time: %d)\n", left[i], seek_time);
        head = left[i];
    }

    printf("\nTotal Seek Time: %d\n", seek_time);
    printf("Average Seek Time: %.2f\n", (float)seek_time / n);

    return 0;
}
