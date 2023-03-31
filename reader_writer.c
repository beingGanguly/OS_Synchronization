#include <stdio.h>

int main()
{
    int n, i, j;
    float avgwt = 0, avgct = 0, avgtat = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int at[n], bt[n], ct[n], tat[n], wt[n], pr[n], is_completed[n];

    printf("Enter the arrival time, burst time, and priority for each process:\n");
    for (i = 0; i < n; i++) {
        printf("Process %d:\n", i+1);
        printf("Arrival time: ");
        scanf("%d", &at[i]);
        printf("Burst time: ");
        scanf("%d", &bt[i]);
        printf("Priority: ");
        scanf("%d", &pr[i]);
        is_completed[i] = 0;
    }

    int time = 0, highest_pr, highest_pr_index;
    while (1) {
        highest_pr = -1;
        highest_pr_index = -1;

        for (i = 0; i < n; i++) {
            if (at[i] <= time && is_completed[i] == 0) {
                if (pr[i] > highest_pr) {
                    highest_pr = pr[i];
                    highest_pr_index = i;
                }
            }
        }

        if (highest_pr_index == -1) {
            time++;
            continue;
        }

        ct[highest_pr_index] = time + bt[highest_pr_index];
        tat[highest_pr_index] = ct[highest_pr_index] - at[highest_pr_index];
        wt[highest_pr_index] = tat[highest_pr_index] - bt[highest_pr_index];
        avgwt += wt[highest_pr_index];
        avgtat += tat[highest_pr_index];
        avgct += ct[highest_pr_index];

        is_completed[highest_pr_index] = 1;
        time = ct[highest_pr_index];

        int completed = 1;
        for (i = 0; i < n; i++) {
            if (is_completed[i] == 0) {
                completed = 0;
                break;
            }
        }

        if (completed == 1) {
            break;
        }
    }

    avgwt /= n;
    avgct /= n;
    avgtat /= n;

    printf("\nProcess\tArrival time\tBurst time\tPriority\tCompletion time\tTurn-around time\tWaiting time\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t\t%d\n", i+1, at[i], bt[i], pr[i], ct[i], tat[i], wt[i]);
    }
    printf("\nAverage waiting time = %.2f\n", avgwt);
    printf("Average completion time = %.2f\n", avgct);
    printf("Average turn-around time = %.2f\n", avgtat);

    return 0;
}