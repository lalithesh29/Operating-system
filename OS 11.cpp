#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#define KEY 1234
struct msgbuf {
    long mtype;
    char mtext[100];
};
int main() {
    int msqid;
    struct msgbuf data;
    msqid = msgget(KEY, IPC_CREAT | 0666);
    if (msqid == -1) {
        perror("msgget");
        exit(1);
    }
    data.mtype = 1;
    strcpy(data.mtext, "Hello from process 1!");
    msgsnd(msqid, &data, strlen(data.mtext) + 1, 0);
    msgctl(msqid, IPC_RMID, NULL); 
    return 0;
}
