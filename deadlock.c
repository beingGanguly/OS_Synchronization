#include <stdio.h>

#define MAX_PROCESSES 100
#define MAX_RESOURCES 100

int allocation[MAX_PROCESSES][MAX_RESOURCES];
int max[MAX_PROCESSES][MAX_RESOURCES];
int available[MAX_RESOURCES];
int need[MAX_PROCESSES][MAX_RESOURCES];
int safe_sequence[MAX_PROCESSES];
int finished[MAX_PROCESSES];
int num_processes, num_resources;

void calculate_need_matrix() {
    for(int i=0;i<num_processes;i++) {
        for(int j=0;j<num_resources;j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
}

int is_finished(int process_id) {
    for(int i=0;i<num_resources;i++) {
        if(need[process_id][i] > available[i]) {
            return 0;
        }
    }
    return 1;
}

int is_deadlock() {
    int finished_processes = 0;
    int check_again = 1;
    while(check_again) {
        check_again = 0;
        for(int i=0;i<num_processes;i++) {
            if(!finished[i] && is_finished(i)) {
                finished_processes++;
                finished[i] = 1;
                safe_sequence[finished_processes-1] = i;
                for(int j=0;j<num_resources;j++) {
                    available[j] += allocation[i][j];
                }
                check_again = 1;
            }
        }
    }
    if(finished_processes == num_processes) {
        return 0;
    }
    return 1;
}

int main() {
    printf("Enter number of processes: ");
    scanf("%d", &num_processes);

    printf("Enter number of resources: ");
    scanf("%d", &num_resources);

    printf("Enter allocation matrix:\n");
    for(int i=0;i<num_processes;i++) {
        for(int j=0;j<num_resources;j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    printf("Enter max matrix:\n");
    for(int i=0;i<num_processes;i++) {
        for(int j=0;j<num_resources;j++) {
            scanf("%d", &max[i][j]);
        }
    }

    printf("Enter available resources:\n");
    for(int i=0;i<num_resources;i++) {
        scanf("%d", &available[i]);
    }

    calculate_need_matrix();

    if(is_deadlock()) {
        printf("Deadlock detected\n");
    } else {
        printf("No deadlock detected\n");
    }

    return 0;
}
