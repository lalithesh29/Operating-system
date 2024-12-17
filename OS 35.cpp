#include <stdio.h>
#include <stdlib.h>

struct Block {
    int blockNumber;
    char data[256]; 
};

int main() {
    FILE *file;
    struct Block block;
    int blockNumber;
    
    long indexBlock[100] = {0}; 

    file = fopen("indexed_file.txt", "w");
    if (file == NULL) {
        printf("Error opening the file.\n");
        return 1;
    }

    printf("Enter blocks (Enter '0' as block number to exit):\n");
    while (1) {
        printf("Block Number: ");
        scanf("%d", &block.blockNumber);
        
        if (block.blockNumber == 0) {
            break;
        }

        // Input data for the block
        printf("Data: ");
        scanf(" %[^\n]", block.data); // Read entire line, including spaces

        // Update the index block with the pointer to the data block
        long currentPos = ftell(file); // Store current position in the file
        
        // Write the block to the file
        fwrite(&block, sizeof(struct Block), 1, file);
        
        // Update the index block with the offset of the block
        indexBlock[block.blockNumber] = currentPos;
    }

    fclose(file); // Close the file after writing

    // Reopen the file in read mode (for reading blocks)
    file = fopen("indexed_file.txt", "r");
    if (file == NULL) {
        printf("Error opening the file.\n");
        return 1;
    }

    // Read a specific block from the file
    while (1) {
        printf("Enter the block number to read (0 to exit): ");
        scanf("%d", &blockNumber);

        if (blockNumber == 0) {
            break;
        }

        // Check if the block exists in the index block
        if (indexBlock[blockNumber] == 0) {
            printf("Block %d not found.\n", blockNumber);
        } else {
            // Seek to the data block using the index block
            fseek(file, indexBlock[blockNumber], SEEK_SET);
            fread(&block, sizeof(struct Block), 1, file);
            
            printf("Block Number: %d\n", block.blockNumber);
            printf("Data: %s\n", block.data);
        }
    }

    fclose(file); // Close the file after reading
    return 0;
}

