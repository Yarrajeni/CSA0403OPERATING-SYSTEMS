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
    int usageHistory[MAX_FRAMES]; // To store usage history of pages

    // Initialize frames and usage history
    for (int i = 0; i < MAX_FRAMES; i++) {
        frames[i] = -1;  // Indicating empty
        usageHistory[i] = 0;
    }

    int pageFaults = 0;
    int referenceString[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};
    int n = sizeof(referenceString) / sizeof(referenceString[0]);

    printf("Reference String: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", referenceString[i]);
    }
    printf("\n\n");

    printf("Page Replacement Order:\n");

    // LRU Page Replacement Logic
    for (int i = 0; i < n; i++) {
        int page = referenceString[i];
        int pageFound = 0;

        // Check if the page is already in memory (page hit)
        for (int j = 0; j < MAX_FRAMES; j++) {
            if (frames[j] == page) {
                pageFound = 1;
                // Reset the usage history for the found page
                for (int k = 0; k < MAX_FRAMES; k++) {
                    if (k != j) {
                        usageHistory[k]++;
                    }
                }
                usageHistory[j] = 0;
                break;
            }
        }

        // If the page is not found, replace the least recently used page
        if (!pageFound) {
            printf("Page %d -> ", page);

            // Find the page with the highest usageHistory value (LRU page)
            int lruPage = 0;
            for (int j = 1; j < MAX_FRAMES; j++) {
                if (usageHistory[j] > usageHistory[lruPage]) {
                    lruPage = j;
                }
            }

            int replacedPage = frames[lruPage];
            frames[lruPage] = page;
            usageHistory[lruPage] = 0;

            // Increase usage counters for all other pages
            for (int j = 0; j < MAX_FRAMES; j++) {
                if (j != lruPage) {
                    usageHistory[j]++;
                }
            }

            if (replacedPage != -1) {
                printf("Replace %d with %d: ", replacedPage, page);
            } else {
                printf("Load into an empty frame: ");
            }
            printFrames(frames, MAX_FRAMES);
            pageFaults++;
        }
    }

    printf("\nTotal Page Faults: %d\n", pageFaults);
    return 0;
}
