#include <stdio.h>
#include <stdlib.h>

struct Process {
    int id, burst_time, priority;
};

void sortProcesses(struct Process proc[], int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (proc[j].priority > proc[j + 1].priority) {
                struct Process temp = proc[j];
                proc[j] = proc[j + 1];
                proc[j + 1] = temp;
            }
}

void preemptivePriorityScheduling(struct Process proc[], int n) {
    sortProcesses(proc, n);
    int time = 0;
    printf("Process Execution Order:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d (Priority: %d) executed for %d units\n", proc[i].id, proc[i].priority, proc[i].burst_time);
        time += proc[i].burst_time;
    }
    printf("Total time: %d\n", time);
}

int main() {
    struct Process proc[] = {{1, 5, 2}, {2, 3, 1}, {3, 8, 3}};
    int n = sizeof(proc) / sizeof(proc[0]);
    preemptivePriorityScheduling(proc, n);
    return 0;
}

