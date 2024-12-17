#include <stdio.h>
#include <string.h>

int main() {
    char fn[100], pat[100], temp[200];
    FILE *fp;

    printf("Enter file name: ");
    scanf("%s", fn);
    printf("Enter the pattern: ");
    scanf("%s", pat);

    fp = fopen(fn, "r");
    if (fp == NULL) {
        printf("Error: Could not open file '%s'.\n", fn);
        return 1;
    }

    printf("Lines containing the pattern '%s':\n", pat);
    while (fgets(temp, sizeof(temp), fp) != NULL) {
        if (strstr(temp, pat) != NULL) {
            printf("%s", temp); 
        }
    }

    fclose(fp);
    return 0;
}

