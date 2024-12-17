#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

extern int errno;

int main() {
    // Open a file named "foo.txt" in read-only mode; create it if it doesn't exist
    int fd = open("foo.txt", O_RDONLY | O_CREAT, S_IRUSR | S_IWUSR);

    // Print the file descriptor
    printf("fd = %d\n", fd);

    // Check if file descriptor is invalid
    if (fd == -1) {
        // Print the error number
        printf("Error Number: %d\n", errno);
        // Print the error description
        perror("Program");
    } else {
        // File opened/created successfully
        printf("File 'foo.txt' opened successfully.\n");
        close(fd); // Close the file descriptor
    }

    return 0;
}

