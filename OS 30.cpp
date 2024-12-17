#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void* func(void* arg) {
    printf("Inside the thread\n");
    pthread_exit(NULL);  
}

void fun() {
    pthread_t ptid;
    if (pthread_create(&ptid, NULL, &func, NULL) != 0) {
        perror("Failed to create thread");
        exit(1);
    }
    printf("This line may be printed before thread terminates\n");

    if (pthread_equal(ptid, pthread_self())) {
        printf("Threads are equal\n");
    } else {
        printf("Threads are not equal\n");
    }

    pthread_join(ptid, NULL);
    printf("This line will be printed after thread ends\n");
}

int main() {
    fun();  // Call the function that creates and joins the thread
    return 0;
}

