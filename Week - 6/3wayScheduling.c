#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct {
    int id;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int priority; // Lower value means higher priority
    int completion_time;
    int waiting_time;
    int turnaround_time;
    int start_time;
} Customer;

void calculate_avg_times(Customer c[], int n, float *avg_wt, float *avg_tt) {
    int total_wt = 0, total_tt = 0;
    for (int i = 0; i < n; i++) {
        c[i].turnaround_time = c[i].completion_time - c[i].arrival_time;
        c[i].waiting_time = c[i].turnaround_time - c[i].burst_time;
        total_wt += c[i].waiting_time;
        total_tt += c[i].turnaround_time;
    }
    *avg_wt = (float)total_wt / n;
    *avg_tt = (float)total_tt / n;
}

void display_gantt_chart(Customer c[], int n) {
    printf("\nGantt Chart:\n|");
    for (int i = 0; i < n; i++) {
        printf(" C%d |", c[i].id);
    }
    printf("\n0");
    for (int i = 0; i < n; i++) {
        printf("    %d", c[i].completion_time);
    }
    printf("\n");
}

void fcfs(Customer c[], int n) {
    printf("\n--- Case 1: First Come First Serve ---\n");
    Customer temp_c[MAX];
    for (int i = 0; i < n; i++) temp_c[i] = c[i];
    
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (temp_c[j].arrival_time > temp_c[j+1].arrival_time) {
                Customer temp = temp_c[j];
                temp_c[j] = temp_c[j+1];
                temp_c[j+1] = temp;
            }
        }
    }

    int current_time = 0;
    for (int i = 0; i < n; i++) {
        if (current_time < temp_c[i].arrival_time) {
            current_time = temp_c[i].arrival_time;
        }
        current_time += temp_c[i].burst_time;
        temp_c[i].completion_time = current_time;
    }

    float avg_wt, avg_tt;
    calculate_avg_times(temp_c, n, &avg_wt, &avg_tt);
    display_gantt_chart(temp_c, n);
    printf("Average Waiting Time: %.2f\n", avg_wt);
    printf("Average Turnaround Time: %.2f\n", avg_tt);
}

void sjf_preemptive(Customer c[], int n) {
    printf("\n--- Case 2: Shortest Remaining Time First (Preemptive SJF) ---\n");
    Customer temp_c[MAX];
    for (int i = 0; i < n; i++) {
        temp_c[i] = c[i];
        temp_c[i].remaining_time = temp_c[i].burst_time;
        temp_c[i].start_time = -1; // To track first start time
    }

    int current_time = 0;
    int completed_count = 0;
    int last_processed_id = -1;
    
    printf("Gantt Chart:\n|");

    while (completed_count < n) {
        int shortest_job_idx = -1;
        int min_remaining_time = 10000;

        for (int i = 0; i < n; i++) {
            if (temp_c[i].arrival_time <= current_time && temp_c[i].remaining_time > 0) {
                if (temp_c[i].remaining_time < min_remaining_time) {
                    min_remaining_time = temp_c[i].remaining_time;
                    shortest_job_idx = i;
                }
            }
        }

        if (shortest_job_idx == -1) {
            current_time++;
            continue;
        }

        if (shortest_job_idx != last_processed_id) {
            printf(" C%d |", temp_c[shortest_job_idx].id);
            last_processed_id = shortest_job_idx;
        }

        if (temp_c[shortest_job_idx].start_time == -1) {
            temp_c[shortest_job_idx].start_time = current_time;
        }

        temp_c[shortest_job_idx].remaining_time--;
        current_time++;

        if (temp_c[shortest_job_idx].remaining_time == 0) {
            temp_c[shortest_job_idx].completion_time = current_time;
            completed_count++;
        }
    }
    printf("\n0");
    for (int i = 0; i < n; i++) {
        printf("    %d", temp_c[i].completion_time);
    }
    printf("\n");
    
    float avg_wt, avg_tt;
    calculate_avg_times(temp_c, n, &avg_wt, &avg_tt);
    printf("Average Waiting Time: %.2f\n", avg_wt);
    printf("Average Turnaround Time: %.2f\n", avg_tt);
}

void priority_preemptive(Customer c[], int n) {
    printf("\n--- Case 3: Priority Scheduling (Preemptive) ---\n");
    Customer temp_c[MAX];
    for (int i = 0; i < n; i++) {
        temp_c[i] = c[i];
        temp_c[i].remaining_time = temp_c[i].burst_time;
        temp_c[i].start_time = -1;
    }

    int current_time = 0;
    int completed_count = 0;
    int last_processed_id = -1;
    
    printf("Gantt Chart:\n|");

    while (completed_count < n) {
        int highest_priority_idx = -1;
        int min_priority = 1000;

        for (int i = 0; i < n; i++) {
            if (temp_c[i].arrival_time <= current_time && temp_c[i].remaining_time > 0) {
                if (temp_c[i].priority < min_priority) {
                    min_priority = temp_c[i].priority;
                    highest_priority_idx = i;
                }
            }
        }

        if (highest_priority_idx == -1) {
            current_time++;
            continue;
        }

        if (highest_priority_idx != last_processed_id) {
            printf(" C%d |", temp_c[highest_priority_idx].id);
            last_processed_id = highest_priority_idx;
        }

        if (temp_c[highest_priority_idx].start_time == -1) {
            temp_c[highest_priority_idx].start_time = current_time;
        }

        temp_c[highest_priority_idx].remaining_time--;
        current_time++;

        if (temp_c[highest_priority_idx].remaining_time == 0) {
            temp_c[highest_priority_idx].completion_time = current_time;
            completed_count++;
        }
    }
    printf("\n0");
    for (int i = 0; i < n; i++) {
        printf("    %d", temp_c[i].completion_time);
    }
    printf("\n");

    float avg_wt, avg_tt;
    calculate_avg_times(temp_c, n, &avg_wt, &avg_tt);
    printf("Average Waiting Time: %.2f\n", avg_wt);
    printf("Average Turnaround Time: %.2f\n", avg_tt);
}

void round_robin(Customer c[], int n, int time_quantum) {
    printf("\n--- Case 4: Round Robin (Time Quantum = %d) ---\n", time_quantum);
    Customer temp_c[MAX];
    for (int i = 0; i < n; i++) {
        temp_c[i] = c[i];
        temp_c[i].remaining_time = temp_c[i].burst_time;
    }

    int time = 0;
    int completed = 0;
    int queue[MAX], front = 0, rear = 0;
    int visited[MAX] = {0};

    // Add the first customer(s) who arrive at time 0
    for (int i = 0; i < n; i++) {
        if (temp_c[i].arrival_time <= time && !visited[i]) {
            queue[rear++] = i;
            visited[i] = 1;
        }
    }

    printf("Gantt Chart:\n|");
    while (completed < n) {
        if (front == rear) {
            int min_arrival = 100000;
            for (int i = 0; i < n; i++) {
                if (!visited[i] && temp_c[i].arrival_time < min_arrival) {
                    min_arrival = temp_c[i].arrival_time;
                }
            }
            time = min_arrival;
            for (int i = 0; i < n; i++) {
                if (temp_c[i].arrival_time <= time && !visited[i]) {
                    queue[rear++] = i;
                    visited[i] = 1;
                }
            }
        }

        int idx = queue[front++];
        if (front == MAX) front = 0;

        int exec_time = (temp_c[idx].remaining_time > time_quantum) ? time_quantum : temp_c[idx].remaining_time;
        printf(" C%d |", temp_c[idx].id);
        time += exec_time;
        temp_c[idx].remaining_time -= exec_time;

        for (int i = 0; i < n; i++) {
            if (temp_c[i].arrival_time <= time && !visited[i]) {
                queue[rear++] = i;
                visited[i] = 1;
                if (rear == MAX) rear = 0;
            }
        }

        if (temp_c[idx].remaining_time > 0) {
            queue[rear++] = idx;
            if (rear == MAX) rear = 0;
        } else {
            temp_c[idx].completion_time = time;
            completed++;
        }
    }
    printf("\n0");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (c[j].id == i + 1) {
                c[j].completion_time = temp_c[j].completion_time;
                break;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        printf("    %d", temp_c[i].completion_time);
    }
    printf("\n");

    float avg_wt, avg_tt;
    calculate_avg_times(temp_c, n, &avg_wt, &avg_tt);
    printf("Average Waiting Time: %.2f\n", avg_wt);
    printf("Average Turnaround Time: %.2f\n", avg_tt);
}

int main() {
    int n, tq;
    Customer customers[MAX];
    printf("Enter number of customers: ");
    scanf("%d", &n);

    printf("Enter customer details (ArrivalTime BurstTime Priority[1-Platinum,2-Gold,3-Silver,4-Normal]):\n");
    for (int i = 0; i < n; i++) {
        customers[i].id = i + 1;
        printf("Customer %d: ", i + 1);
        scanf("%d %d %d", &customers[i].arrival_time, &customers[i].burst_time, &customers[i].priority);
    }

    // Create copies for each algorithm
    Customer fcfs_customers[MAX], sjf_customers[MAX], priority_customers[MAX], rr_customers[MAX];
    for (int i = 0; i < n; i++) {
        fcfs_customers[i] = customers[i];
        sjf_customers[i] = customers[i];
        priority_customers[i] = customers[i];
        rr_customers[i] = customers[i];
    }

    fcfs(fcfs_customers, n);
    sjf_preemptive(sjf_customers, n);
    priority_preemptive(priority_customers, n);
    round_robin(rr_customers, n, 5); // Time quantum = 5

    return 0;
}
