#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Block {
    char data[256]; 
    struct Block* next; 
};

int main() {
    struct Block* firstBlock = NULL; 
    struct Block* lastBlock = NULL;  
    int blockCount = 0;              
    int blockNumber;
    char data[256];
    char choice;

    printf("Linked Allocation Simulation\n");

    while (1) {
        printf("Enter 'W' to write a block, 'R' to read a block, or 'Q' to quit: ");
        scanf(" %c", &choice);  

        if (choice == 'Q' || choice == 'q') {
            break;
        }

        if (choice == 'W' || choice == 'w') {
            printf("Enter data for the block: ");
            scanf(" %[^\n]", data);  // Read entire line, including spaces

            // Create a new block
            struct Block* newBlock = (struct Block*)malloc(sizeof(struct Block));
            if (newBlock == NULL) {
                printf("Memory allocation failed!\n");
                return 1;
            }

            // Copy data into the block's data array
            strcpy(newBlock->data, data);
            newBlock->next = NULL;

            // Link the new block to the list
            if (blockCount == 0) {
                // This is the first block
                firstBlock = newBlock;
                lastBlock = newBlock;
            } else {
                // Link the new block to the last block
                lastBlock->next = newBlock;
                lastBlock = newBlock;
            }

            blockCount++;
        } else if (choice == 'R' || choice == 'r') {
            printf("Enter the block number to read (1-%d): ", blockCount);
            scanf("%d", &blockNumber);

            if (blockNumber < 1 || blockNumber > blockCount) {
                printf("Invalid block number. The valid range is 1-%d.\n", blockCount);
            } else {
                // Traverse to the desired block
                struct Block* currentBlock = firstBlock;
                for (int i = 1; i < blockNumber; i++) {
                    currentBlock = currentBlock->next;
                }

                // Print the data of the block
                printf("Block %d Data: %s\n", blockNumber, currentBlock->data);
            }
        }
    }

    // Free the allocated memory for blocks before exiting
    struct Block* currentBlock = firstBlock;
    while (currentBlock != NULL) {
        struct Block* nextBlock = currentBlock->next;
        free(currentBlock);  // Free the current block
        currentBlock = nextBlock;
    }

    return 0;
}

