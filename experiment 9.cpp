#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

int main() {
    int shmid;
    key_t key = 1234;
    char *str;

    shmid = shmget(key, 1024, 0666|IPC_CREAT);
    str = (char*) shmat(shmid, NULL, 0);

    printf("Write Data: ");
    fgets(str, 1024, stdin);
    printf("Data written in memory: %s\n", str);

    shmdt(str);
    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}

