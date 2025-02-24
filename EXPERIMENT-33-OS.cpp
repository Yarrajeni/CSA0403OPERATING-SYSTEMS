#include <stdio.h>

#define MAX_FRAMES 3 // Maximum number of frames in memory

// Function to print the current frame state
void printFrames(int frames[], int n) {
    for (int i = 0; i < n; i++) {
        if (frames[i] == -1) {
            printf(" - ");
        } else {
            printf(" %d ", frames[i]);
        }
    }
    printf("\n");
}

int main() {
    int frames[MAX_FRAMES];
    int pageFaults = 0;

    // Initialize frames to -1 (indicating empty)
    for (int i = 0; i < MAX_FRAMES; i++) {
        frames[i] = -1;
    }

    int referenceString[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};
    int n = sizeof(referenceString) / sizeof(referenceString[0]);

    printf("Reference String: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", referenceString[i]);
    }
    printf("\n\n");

    printf("Page Replacement Order:\n");

    for (int i = 0; i < n; i++) {
        int page = referenceString[i];
        int pageFound = 0;

        // Check if the page is already in memory (page hit)
        for (int j = 0; j < MAX_FRAMES; j++) {
            if (frames[j] == page) {
                pageFound = 1;
                break;
            }
        }

        // If the page is not found, replace a page using the Optimal Page Replacement strategy
        if (!pageFound) {
            printf("Page %d -> ", page);

            // Check if there is an empty frame
            int emptyFrame = -1;
            for (int j = 0; j < MAX_FRAMES; j++) {
                if (frames[j] == -1) {
                    emptyFrame = j;
                    break;
                }
            }

            // If an empty frame is available, use it
            if (emptyFrame != -1) {
                frames[emptyFrame] = page;
            } else {
                // Find the page in memory that will be **used farthest in the future** or **never used again**
                int optimalPage = -1, farthestDistance = -1;

                for (int j = 0; j < MAX_FRAMES; j++) {
                    int futureDistance = n; // Default to a large value
                    for (int k = i + 1; k < n; k++) {
                        if (referenceString[k] == frames[j]) {
                            futureDistance = k;
                            break;
                        }
                    }
                    // Select the page with the **farthest future use** or **never used again**
                    if (futureDistance > farthestDistance) {
                        farthestDistance = futureDistance;
                        optimalPage = j;
                    }
                }

                // Replace the chosen page
                printf("Replace %d with %d: ", frames[optimalPage], page);
                frames[optimalPage] = page;
            }

            printFrames(frames, MAX_FRAMES);
            pageFaults++;
        }
    }

    printf("\nTotal Page Faults: %d\n", pageFaults);
    return 0;
}
