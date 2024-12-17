#include <stdio.h>

#define MAX_MEMORY 1000
int memory[MAX_MEMORY];

// Function to initialize memory
void initializeMemory() {
    for (int i = 0; i < MAX_MEMORY; i++) {
        memory[i] = -1; // -1 indicates that the memory is unallocated
    }
}

// Function to display memory status
void displayMemory() {
    int i, j;
    int count = 0;

    printf("Memory Status:\n");
    for (i = 0; i < MAX_MEMORY; i++) {
        if (memory[i] == -1) {
            count++;
            j = i;
            while (memory[j] == -1 && j < MAX_MEMORY) {
                j++;
            }
            printf("Free memory block %d-%d\n", i, j - 1);
            i = j - 1;
        }
    }
    if (count == 0) {
        printf("No free memory available.\n");
    }
}

// Function to allocate memory using worst-fit algorithm
void allocateMemory(int processId, int size) {
    int start = -1, blockSize = 0, maxBlockSize = 0, maxBlockStart = -1;

    // Find the largest free block
    for (int i = 0; i < MAX_MEMORY; i++) {
        if (memory[i] == -1) {
            if (blockSize == 0) {
                start = i;
            }
            blockSize++;
        } else {
            if (blockSize > maxBlockSize) {
                maxBlockSize = blockSize;
                maxBlockStart = start;
            }
            blockSize = 0;
        }
    }

    // Check the last block if it's the largest
    if (blockSize > maxBlockSize) {
        maxBlockSize = blockSize;
        maxBlockStart = start;
    }

    // Allocate memory if a large enough block is found
    if (maxBlockSize >= size) {
        for (int i = maxBlockStart; i < maxBlockStart + size; i++) {
            memory[i] = processId;
        }
        printf("Allocated memory block %d-%d to Process %d\n", maxBlockStart, maxBlockStart + size - 1, processId);
    } else {
        printf("Memory allocation for Process %d failed (not enough contiguous memory).\n", processId);
    }
}

// Function to deallocate memory
void deallocateMemory(int processId) {
    for (int i = 0; i < MAX_MEMORY; i++) {
        if (memory[i] == processId) {
            memory[i] = -1;
        }
    }
    printf("Memory released by Process %d\n", processId);
}

int main() {
    initializeMemory();

    printf("Initial ");
    displayMemory();

    allocateMemory(1, 200);
    displayMemory();

    allocateMemory(2, 300);
    displayMemory();

    deallocateMemory(1);
    displayMemory();

    allocateMemory(3, 400);
    displayMemory();

    return 0;
}

