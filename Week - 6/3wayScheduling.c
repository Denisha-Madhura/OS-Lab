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
        printf("   %d", c[i].completion_time);
    }
    printf("\n");
}

void fcfs(Customer c[], int n) {
    printf("\n--- Case 1: First Come First Serve ---\n");
    // Sort by arrival time
    for (int i = 0; i < n-1; i++)
        for (int j = 0; j < n-i-1; j++)
            if (c[j].arrival_time > c[j+1].arrival_time)
                { Customer temp = c[j]; c[j] = c[j+1]; c[j+1] = temp; }

    int current_time = 0;
    for (int i = 0; i < n; i++) {
        if (current_time < c[i].arrival_time)
            current_time = c[i].arrival_time;
        current_time += c[i].burst_time;
        c[i].completion_time = current_time;
    }

    float avg_wt, avg_tt;
    calculate_avg_times(c, n, &avg_wt, &avg_tt);
    display_gantt_chart(c, n);
    printf("Average Waiting Time: %.2f\n", avg_wt);
    printf("Average Turnaround Time: %.2f\n", avg_tt);
}

void priority_scheduling(Customer c[], int n) {
    printf("\n--- Case 2: Priority Scheduling ---\n");
    // Sort by priority and arrival time
    for (int i = 0; i < n-1; i++)
        for (int j = 0; j < n-i-1; j++)
            if (c[j].priority > c[j+1].priority ||
               (c[j].priority == c[j+1].priority && c[j].arrival_time > c[j+1].arrival_time))
                { Customer temp = c[j]; c[j] = c[j+1]; c[j+1] = temp; }

    int current_time = 0;
    for (int i = 0; i < n; i++) {
        if (current_time < c[i].arrival_time)
            current_time = c[i].arrival_time;
        current_time += c[i].burst_time;
        c[i].completion_time = current_time;
    }

    float avg_wt, avg_tt;
    calculate_avg_times(c, n, &avg_wt, &avg_tt);
    display_gantt_chart(c, n);
    printf("Average Waiting Time: %.2f\n", avg_wt);
    printf("Average Turnaround Time: %.2f\n", avg_tt);
}

void round_robin(Customer c[], int n, int time_quantum) {
    printf("\n--- Case 3: Round Robin (Time Quantum = %d) ---\n", time_quantum);
    
    int time = 0;               // Current time
    int completed = 0;          // Number of completed customers
    int queue[MAX], front = 0, rear = 0;
    int visited[MAX] = {0};     // Track if customer has been added to queue
    
    for (int i = 0; i < n; i++)
        c[i].remaining_time = c[i].burst_time;

    // Add the first customer(s) who arrive at time 0
    for (int i = 0; i < n; i++) {
        if (c[i].arrival_time <= time && !visited[i]) {
            queue[rear++] = i;
            visited[i] = 1;
        }
    }

    printf("Gantt Chart:\n|");
    while (completed < n) {
        if (front == rear) {
            // If queue is empty, move time to next arrival
            int min_arrival = 100000;
            for (int i = 0; i < n; i++) {
                if (!visited[i]) {
                    if (c[i].arrival_time < min_arrival)
                        min_arrival = c[i].arrival_time;
                }
            }
            time = min_arrival;
            for (int i = 0; i < n; i++) {
                if (c[i].arrival_time <= time && !visited[i]) {
                    queue[rear++] = i;
                    visited[i] = 1;
                }
            }
        }

        int idx = queue[front++];
        if (front == MAX) front = 0; // Circular queue (not strictly necessary here)

        // Process current customer for time quantum or remaining time
        int exec_time = (c[idx].remaining_time > time_quantum) ? time_quantum : c[idx].remaining_time;
        printf(" C%d |", c[idx].id);
        time += exec_time;
        c[idx].remaining_time -= exec_time;

        // Add newly arrived customers to queue
        for (int i = 0; i < n; i++) {
            if (c[i].arrival_time <= time && !visited[i]) {
                queue[rear++] = i;
                visited[i] = 1;
                if (rear == MAX) rear = 0;
            }
        }

        if (c[idx].remaining_time > 0) {
            // Customer still needs service, enqueue again
            queue[rear++] = idx;
            if (rear == MAX) rear = 0;
        } else {
            // Finished customer
            c[idx].completion_time = time;
            completed++;
        }
    }
    printf("\n0");
    // Print time marks on gantt chart
    time = 0;
    for (int i = 0; i < n; i++) {
        time += c[i].burst_time;
        printf("   %d", time);
    }
    printf("\n");

    float avg_wt, avg_tt;
    calculate_avg_times(c, n, &avg_wt, &avg_tt);
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
    Customer fcfs_customers[MAX], priority_customers[MAX], rr_customers[MAX];
    for (int i = 0; i < n; i++) {
        fcfs_customers[i] = customers[i];
        priority_customers[i] = customers[i];
        rr_customers[i] = customers[i];
    }

    fcfs(fcfs_customers, n);
    priority_scheduling(priority_customers, n);
    round_robin(rr_customers, n, 5); // Time quantum = 5

    return 0;
}
