#include <stdio.h>

void findWaitingTime(int processes[], int n, int bt[], int wt[]) {
    wt[0] = 0;
    for (int i = 1; i < n; i++)
        wt[i] = bt[i - 1] + wt[i - 1];
}

void findTurnAroundTime(int processes[], int n, int bt[], int wt[], int tat[]) {
    for (int i = 0; i < n; i++)
        tat[i] = bt[i] + wt[i];
}

void findavgTime(int processes[], int n, int bt[]) {
    int wt[n], tat[n];
    findWaitingTime(processes, n, bt, wt);
    findTurnAroundTime(processes, n, bt, wt, tat);
    
    float total_wt = 0, total_tat = 0;
    for (int i = 0; i < n; i++) {
        total_wt += wt[i];
        total_tat += tat[i];
    }
    printf("Average waiting time: %.2f\n", total_wt / n);
    printf("Average turnaround time: %.2f\n", total_tat / n);
}

void sortProcesses(int processes[], int n, int bt[]) {
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (bt[j] > bt[j + 1]) {
                int temp = bt[j]; bt[j] = bt[j + 1]; bt[j + 1] = temp;
                temp = processes[j]; processes[j] = processes[j + 1]; processes[j + 1] = temp;
            }
}

int main() {
    int processes[] = {1, 2, 3};
    int burst_time[] = {6, 8, 7};
    int n = sizeof(processes) / sizeof(processes[0]);
    
    sortProcesses(processes, n, burst_time);
    findavgTime(processes, n, burst_time);
    
    return 0;
}

