#include <stdio.h>
#include <stdlib.h>

struct Record {
    int recordNumber;
    char data[256]; 
};

int main() {
    FILE *file;
    struct Record record;
    int recordNumber;

    file = fopen("sequential_file.txt", "w");
    if (file == NULL) {
        printf("Error opening the file.\n");
        return 1;
    }

    printf("Enter records (Enter '0' as record number to exit):\n");
    while (1) {
        printf("Record Number: ");
        scanf("%d", &record.recordNumber);
        
        if (record.recordNumber == 0) {
            break;
        }

        // Input data for the record
        printf("Data: ");
        scanf(" %[^\n]", record.data); // To read entire line with spaces
        
        // Write the record to the file
        fwrite(&record, sizeof(struct Record), 1, file);
    }
    fclose(file);  // Close the file after writing

    // Reopen the file in read mode (for reading records)
    file = fopen("sequential_file.txt", "r");
    if (file == NULL) {
        printf("Error opening the file.\n");
        return 1;
    }

    // Read a specific record from the file
    while (1) {
        printf("Enter the record number to read (0 to exit): ");
        scanf("%d", &recordNumber);

        if (recordNumber == 0) {
            break;
        }

        // Read and display records up to the requested record
        int found = 0;  // Flag to check if the record was found
        while (fread(&record, sizeof(struct Record), 1, file)) {
            if (record.recordNumber == recordNumber) {
                printf("Record Number: %d\n", record.recordNumber);
                printf("Data: %s\n", record.data);
                found = 1;
                break;
            }
        }

        if (!found) {
            printf("Record Number %d not found.\n", recordNumber);
        }

        // Reset the file pointer to the beginning of the file for next search
        rewind(file);
    }

    fclose(file);  // Close the file after reading
    return 0;
}

