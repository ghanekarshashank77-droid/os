#include <stdio.h>
#include <limits.h>

struct Process {
    int pid;      
    int at;      
    int bt;        
    int rt;        
    int ct;        
    int tat;      
    int wt;        
    int completed;
};

int main() {
    int n, completed = 0, currentTime = 0, minRT, shortest;
    float totalTAT = 0, totalWT = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    for (int i = 0; i < n; i++) {
        printf("Enter Process ID, Arrival Time, Burst Time for Process %d: ", i + 1);
        scanf("%d%d%d", &p[i].pid, &p[i].at, &p[i].bt);
        p[i].rt = p[i].bt;  
        p[i].completed = 0;  
    }

    printf("\n--- Gantt Chart ---\n");
    printf("0");

    while (completed != n) {
        shortest = -1;
        minRT = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (p[i].at <= currentTime && p[i].completed == 0 && p[i].rt < minRT) {
                minRT = p[i].rt;
                shortest = i;
            }
        }

        if (shortest == -1) {
            printf(" | Idle | %d", currentTime + 1);
            currentTime++;
            continue;
        }

        printf(" | P%d | %d", p[shortest].pid, currentTime + 1);
        p[shortest].rt--;
        currentTime++;

        if (p[shortest].rt == 0) {
            p[shortest].completed = 1;
            completed++;

            p[shortest].ct = currentTime;
            p[shortest].tat = p[shortest].ct - p[shortest].at;
            p[shortest].wt = p[shortest].tat - p[shortest].bt;

            totalTAT += p[shortest].tat;
            totalWT += p[shortest].wt;
        }
    }

    printf("\n");

    printf("\n--- Process Table ---\n");
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt,
               p[i].ct, p[i].tat, p[i].wt);
    }

    printf("\nAverage TAT = %.2f", totalTAT / n);
    printf("\nAverage WT = %.2f\n", totalWT / n);

    return 0;
}


