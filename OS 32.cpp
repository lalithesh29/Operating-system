#include <stdio.h>
#include <stdlib.h>

#define MAX_FRAMES 3

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
    int usageHistory[MAX_FRAMES];      
    
    for (int i = 0; i < MAX_FRAMES; i++) {
        frames[i] = -1;               
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

    // Iterate through the reference string
    for (int i = 0; i < n; i++) {
        int page = referenceString[i];
        int pageFound = 0;

        // Check if the page is already in memory (page hit)
        for (int j = 0; j < MAX_FRAMES; j++) {
            if (frames[j] == page) {
                pageFound = 1;

                // Update usage history: increment the counters for other pages
                for (int k = 0; k < MAX_FRAMES; k++) {
                    if (k != j) {
                        usageHistory[k]++;
                    }
                }

                usageHistory[j] = 0;  // Reset the usage counter for the used page
                break;
            }
        }

        if (!pageFound) {
            printf("Page %d -> ", page);

            // Find the page with the maximum usage counter (least recently used)
            int lruPage = 0;
            for (int j = 1; j < MAX_FRAMES; j++) {
                if (usageHistory[j] > usageHistory[lruPage]) {
                    lruPage = j;
                }
            }

            int replacedPage = frames[lruPage];
            frames[lruPage] = page;           // Replace the least recently used page
            usageHistory[lruPage] = 0;        // Reset the usage history for the new page

            if (replacedPage != -1) {
                printf("Replace %d with %d: ", replacedPage, page);
            } else {
                printf("Load into an empty frame: ");
            }

            // Print the frames after replacement
            printFrames(frames, MAX_FRAMES);
            pageFaults++;
        }
    }

    // Print the total number of page faults
    printf("\nTotal Page Faults: %d\n", pageFaults);

    return 0;
}

