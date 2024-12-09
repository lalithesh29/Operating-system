#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <unistd.h>

#define MSG_SIZE 100

struct msg_buffer {
    long msg_type;
    char msg_text[MSG_SIZE];
};

int main() {
    key_t key = ftok("progfile", 65);
    int msgid = msgget(key, 0666 | IPC_CREAT);
    struct msg_buffer message;

    // Sending message
    message.msg_type = 1;
    strcpy(message.msg_text, "Hello, World!");
    msgsnd(msgid, &message, sizeof(message), 0);

    // Receiving message
    msgrcv(msgid, &message, sizeof(message), 1, 0);
    printf("Received: %s\n", message.msg_text);

    // Destroy the message queue
    msgctl(msgid, IPC_RMID, NULL);
    return 0;
}

