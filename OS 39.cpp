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
    
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (request_queue[i] > request_queue[j]) {
                int temp = request_queue[i];
                request_queue[i] = request_queue[j];
                request_queue[j] = temp;
            }
        }
    }

    // C-SCAN (Circular SCAN) Scheduling
    printf("\nC-SCAN Disk Scheduling:\n");
    
    // Move the head to the right and serve requests
    int start = 0;
    int end = n - 1;
    
    // Move head to the right (serving requests >= head)
    while (start <= end) {
        if (request_queue[start] >= head) {
            seek_time += abs(head - request_queue[start]);
            head = request_queue[start];
            start++;
        } else {
            start++;
        }
    }
    
    // Move the head to the farthest right (end of the disk)
    seek_time += abs(head - 0);
    head = 0;

    // Serve the remaining requests in a circular manner (from 0 to the farthest right)
    for (int i = 0; i <= end; i++) {
        seek_time += abs(head - request_queue[i]);
        head = request_queue[i];
    }
    
    // Output the results
    printf("Total Seek Time: %d\n", seek_time);
    printf("Average Seek Time: %.2f\n", (float)seek_time / n);
    
    return 0;
}

