#include <stdio.h>
#include <stdbool.h>

int n, m;  // number of processes and resources

// Function to calculate and print Need matrix
void printNeedMatrix(int max[20][20], int allot[20][20]) {
    int need[20][20];

    printf("\nNeed Matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            need[i][j] = max[i][j] - allot[i][j];
            printf("%3d ", need[i][j]);
        }
        printf("\n");
    }
}

// Function to check if the system is in a safe state
bool isSafe(int processes[], int avail[], int max[20][20], int allot[20][20]) {
    int need[20][20];
    int work[20], finish[20];

    // Calculate Need matrix
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            need[i][j] = max[i][j] - allot[i][j];

    // Initialize work = avail, finish = false
    for (int i = 0; i < m; i++)
        work[i] = avail[i];
    for (int i = 0; i < n; i++)
        finish[i] = 0;

    int safeSeq[20], count = 0;

    while (count < n) {
        bool found = false;
        for (int p = 0; p < n; p++) {
            if (finish[p] == 0) {
                int j;
                for (j = 0; j < m; j++)
                    if (need[p][j] > work[j])
                        break;

                if (j == m) {
                    for (int k = 0; k < m; k++)
                        work[k] += allot[p][k];

                    safeSeq[count++] = p;
                    finish[p] = 1;
                    found = true;
                }
            }
        }
        if (!found) {
            printf("System is NOT in a safe state.\n");
            return false;
        }
    }

    printf("System is in a SAFE state.\nSafe sequence: ");
    for (int i = 0; i < n; i++)
        printf("P%d ", safeSeq[i]);
    printf("\n");

    return true;
}

// Function to process a resource request
void requestResources(int processes[], int avail[], int max[20][20], int allot[20][20], int reqProcess, int request[]) {
    int need[20][20];

    // Calculate Need matrix
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            need[i][j] = max[i][j] - allot[i][j];

    // Check if request <= need
    for (int j = 0; j < m; j++) {
        if (request[j] > need[reqProcess][j]) {
            printf("Error: Process has exceeded its maximum claim.\n");
            return;
        }
    }

    // Check if request <= available
    for (int j = 0; j < m; j++) {
        if (request[j] > avail[j]) {
            printf("Process must wait since resources are not available.\n");
            return;
        }
    }

    // Pretend to allocate resources
    for (int j = 0; j < m; j++) {
        avail[j] -= request[j];
        allot[reqProcess][j] += request[j];
        need[reqProcess][j] -= request[j];
    }

    // Check if safe
    if (isSafe(processes, avail, max, allot)) {
        printf("Request can be granted.\n");
    } else {
        // Rollback
        for (int j = 0; j < m; j++) {
            avail[j] += request[j];
            allot[reqProcess][j] -= request[j];
            need[reqProcess][j] += request[j];
        }
        printf("Request cannot be granted as system would be unsafe.\n");
    }

    // Print updated Need matrix
    printNeedMatrix(max, allot);
}

int main() {
    int processes[20];
    int avail[20], max[20][20], allot[20][20];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resources: ");
    scanf("%d", &m);

    for (int i = 0; i < n; i++)
        processes[i] = i;

    printf("Enter Available resources (for each of %d types):\n", m);
    for (int i = 0; i < m; i++)
        scanf("%d", &avail[i]);

    printf("Enter Max matrix (%d x %d):\n", n, m);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &max[i][j]);

    printf("Enter Allocation matrix (%d x %d):\n", n, m);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &allot[i][j]);

    // Print initial Need matrix
    printNeedMatrix(max, allot);

    // First check system state
    printf("\n--- Checking initial system state ---\n");
    isSafe(processes, avail, max, allot);

    // Request loop
    char choice;
    do {
        int reqProcess;
        printf("\nEnter process number making request (0 to %d): ", n - 1);
        scanf("%d", &reqProcess);

        int request[20];
        printf("Enter request vector of process P%d (for %d resources):\n", reqProcess, m);
        for (int i = 0; i < m; i++)
            scanf("%d", &request[i]);

        requestResources(processes, avail, max, allot, reqProcess, request);

        printf("\nDo you want to enter another request? (y/n): ");
        scanf(" %c", &choice);

    } while (choice == 'y' || choice == 'Y');

    return 0;
}
