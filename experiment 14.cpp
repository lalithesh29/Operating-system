#include <stdio.h>
#include <string.h>

#define MAX_FILES 100
#define MAX_DIRS 10
#define MAX_NAME_LENGTH 50

typedef struct {
    char name[MAX_NAME_LENGTH];
} File;

typedef struct {
    char name[MAX_NAME_LENGTH];
    File files[MAX_FILES];
    int file_count;
} SubDirectory;

typedef struct {
    SubDirectory subdirs[MAX_DIRS];
    int dir_count;
} Directory;

void addFile(Directory *dir, const char *subDirName, const char *fileName) {
    for (int i = 0; i < dir->dir_count; i++) {
        if (strcmp(dir->subdirs[i].name, subDirName) == 0) {
            strcpy(dir->subdirs[i].files[dir->subdirs[i].file_count++].name, fileName);
            return;
        }
    }
}

void listFiles(const Directory *dir, const char *subDirName) {
    for (int i = 0; i < dir->dir_count; i++) {
        if (strcmp(dir->subdirs[i].name, subDirName) == 0) {
            for (int j = 0; j < dir->subdirs[i].file_count; j++) {
                printf("%s\n", dir->subdirs[i].files[j].name);
            }
        }
    }
}

int main() {
    Directory dir = {.dir_count = 2};
    strcpy(dir.subdirs[0].name, "subdir1");
    strcpy(dir.subdirs[1].name, "subdir2");

    addFile(&dir, "subdir1", "file1.txt");
    addFile(&dir, "subdir1", "file2.txt");
    addFile(&dir, "subdir2", "file3.txt");

    printf("Files in subdir1:\n");
    listFiles(&dir, "subdir1");

    printf("Files in subdir2:\n");
    listFiles(&dir, "subdir2");

    return 0;
}

