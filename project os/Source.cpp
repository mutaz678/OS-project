#include <iostream>
using namespace std;

void findWaitingTime(int processes[], int n, int bt[], int wt[], int quantum) {
    int* rem_bt = new int[n];  // Dynamic memory allocation for rem_bt
    for (int i = 0; i < n; i++)
        rem_bt[i] = bt[i];

    int t = 0;

    while (true) {
        bool done = true;

        for (int i = 0; i < n; i++) {
            if (rem_bt[i] > 0) {
                done = false;

                if (rem_bt[i] > quantum) {
                    t += quantum;
                    rem_bt[i] -= quantum;
                }
                else {
                    t += rem_bt[i];
                    wt[i] = t - bt[i];
                    rem_bt[i] = 0;
                }
            }
        }

        if (done)
            break;
    }

    delete[] rem_bt;  // Release dynamically allocated memory
}

void findTurnAroundTime(int processes[], int n, int bt[], int wt[], int tat[]) {
    for (int i = 0; i < n; i++)
        tat[i] = bt[i] + wt[i];
}

void findavgTime(int processes[], int n, int bt[], int quantum) {
    int* wt = new int[n];
    int* tat = new int[n];
    int total_wt = 0;
    int total_tat = 0;

    findWaitingTime(processes, n, bt, wt, quantum);
    findTurnAroundTime(processes, n, bt, wt, tat);

    cout << "Processes\tBurst time\tWaiting time\tTurnaround time\n";

    for (int i = 0; i < n; i++) {
        total_wt += wt[i];
        total_tat += tat[i];
        cout << " " << i + 1 << "\t\t" << bt[i] << "\t\t" << wt[i] << "\t\t " << tat[i] << endl;
    }

    cout << "Average waiting time = " << (float)total_wt / (float)n << endl;
    cout << "Average turnaround time = " << (float)total_tat / (float)n << endl;

    delete[] wt;
    delete[] tat;
}

int main() {
    int processes[] = { 1, 2, 3 };
    int n = sizeof processes / sizeof processes[0];
    int burst_time[] = { 10, 5, 8 };
    int quantum = 2;

    findavgTime(processes, n, burst_time, quantum);

    return 0;
}
