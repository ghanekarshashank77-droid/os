#include <stdio.h>

struct Process {
    int pid;
    int at;
    int bt;
    int ct;
    int tat;
    int wt;
};

void sortByArrival(struct Process p[], int n) {
    struct Process temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (p[i].at > p[j].at) {
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];
    int start_time[n];
    float total_tat = 0, total_wt = 0;

    // Input
    for (int i = 0; i < n; i++) {
        printf("Enter Process ID, Arrival Time and Burst Time for process %d: ", i + 1);
        scanf("%d%d%d", &p[i].pid, &p[i].at, &p[i].bt);
    }

    // Sort by Arrival Time
    sortByArrival(p, n);

    int time = 0;

    // FCFS Scheduling
    for (int i = 0; i < n; i++) {
        if (time < p[i].at)
            time = p[i].at;

        start_time[i] = time;

        p[i].ct = time + p[i].bt;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;

        total_tat += p[i].tat;
        total_wt += p[i].wt;

        time = p[i].ct;
    }

    // Output Table
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }

    printf("\nAverage Turnaround Time: %.2f", total_tat / n);
    printf("\nAverage Waiting Time   : %.2f\n", total_wt / n);

    // Gantt Chart
    printf("\nGantt Chart:\n");

    // Top bar
    printf(" ");
    for (int i = 0; i < n; i++) {
        printf("--------");
    }
    printf("-\n|");

    // Process IDs
    for (int i = 0; i < n; i++) {
        printf("  P%d   |", p[i].pid);
    }

    // Bottom bar
    printf("\n ");
    for (int i = 0; i < n; i++) {
        printf("--------");
    }
    printf("-\n");

    // Timeline
    printf("%d", start_time[0]);
    for (int i = 0; i < n; i++) {
        printf("       %d", p[i].ct);
    }

    printf("\n");

    return 0;
}

