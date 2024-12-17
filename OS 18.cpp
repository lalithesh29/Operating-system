#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t mutex, writeBlock;
int data = 0, readersCount = 0;

void* reader(void* arg) {
    for (int i = 0; i < 10; ++i) {
        sem_wait(&mutex);
        readersCount++;
        if (readersCount == 1) {
            sem_wait(&writeBlock);
        }
        sem_post(&mutex);

        // Reading operation
        printf("Reader reads data: %d\n", data);

        sem_wait(&mutex);
        readersCount--;
        if (readersCount == 0) {
            sem_post(&writeBlock);
        }
        sem_post(&mutex);
    }
    return NULL;
}

void* writer(void* arg) {
    for (int i = 0; i < 10; ++i) {
        sem_wait(&writeBlock);

        // Writing operation
        data++;
        printf("Writer writes data: %d\n", data);

        sem_post(&writeBlock);
    }
    return NULL;
}

int main() {
    pthread_t readerThread, writerThread;

    sem_init(&mutex, 0, 1);
    sem_init(&writeBlock, 0, 1);

    pthread_create(&readerThread, NULL, reader, NULL);
    pthread_create(&writerThread, NULL, writer, NULL);

    pthread_join(readerThread, NULL);
    pthread_join(writerThread, NULL);

    sem_destroy(&mutex);
    sem_destroy(&writeBlock);

    return 0;
}

