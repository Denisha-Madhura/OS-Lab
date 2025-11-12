#include <stdio.h>
#include <stdlib.h>

void copyArray(int dest[], const int src[], int size) {
    for (int i = 0; i < size; i++) {
        dest[i] = src[i];
    }
}

void firstFit(int partitions[], int p_count, int processes[], int j_count) {
    int allocated_partitions[j_count];
    int initial_partition_sizes[j_count];
    int current_partitions[p_count];
    
    copyArray(current_partitions, partitions, p_count);

    for (int i = 0; i < j_count; i++) {
        allocated_partitions[i] = -1;
        initial_partition_sizes[i] = -1;
        for (int j = 0; j < p_count; j++) {
            if (current_partitions[j] >= processes[i]) {
                allocated_partitions[i] = j;
                initial_partition_sizes[i] = current_partitions[j];
                current_partitions[j] = 0;
                break;
            }
        }
    }

    printf("--- First Fit Allocation Order ---\n");
    for (int i = 0; i < j_count; i++) {
        if (allocated_partitions[i] != -1) {
            printf("Process %d (%dkB) allocated to Partition %d (Initial: %dkB, Remaining: %dkB)\n", 
                   i + 1, processes[i], 
                   allocated_partitions[i] + 1, 
                   initial_partition_sizes[i], 
                   current_partitions[allocated_partitions[i]]);
        } else {
            printf("Process %d (%dkB) could not be allocated\n", i + 1, processes[i]);
        }
    }
}

void bestFit(int partitions[], int p_count, int processes[], int j_count) {
    int allocated_partitions[j_count];
    int initial_partition_sizes[j_count];
    int current_partitions[p_count];
    
    copyArray(current_partitions, partitions, p_count);

    for (int i = 0; i < j_count; i++) {
        int best_idx = -1;
        int min_fragmentation = 2147483647; 
        allocated_partitions[i] = -1;
        initial_partition_sizes[i] = -1;

        for (int j = 0; j < p_count; j++) {
            if (current_partitions[j] >= processes[i]) {
                int fragmentation = current_partitions[j] - processes[i];
                if (fragmentation < min_fragmentation) {
                    min_fragmentation = fragmentation;
                    best_idx = j;
                }
            }
        }

        if (best_idx != -1) {
            allocated_partitions[i] = best_idx;
            initial_partition_sizes[i] = current_partitions[best_idx];
            current_partitions[best_idx] = 0;
        }
    }

    printf("\n--- Best Fit Allocation Order ---\n");
    for (int i = 0; i < j_count; i++) {
        if (allocated_partitions[i] != -1) {
            printf("Process %d (%dkB) allocated to Partition %d (Initial: %dkB, Remaining: %dkB)\n", 
                   i + 1, processes[i], 
                   allocated_partitions[i] + 1, 
                   initial_partition_sizes[i], 
                   current_partitions[allocated_partitions[i]]);
        } else {
            printf("Process %d (%dkB) could not be allocated\n", i + 1, processes[i]);
        }
    }
}

void worstFit(int partitions[], int p_count, int processes[], int j_count) {
    int allocated_partitions[j_count];
    int initial_partition_sizes[j_count];
    int current_partitions[p_count];
    
    copyArray(current_partitions, partitions, p_count);

    for (int i = 0; i < j_count; i++) {
        int worst_idx = -1;
        int max_fragmentation = -1; 
        allocated_partitions[i] = -1;
        initial_partition_sizes[i] = -1;

        for (int j = 0; j < p_count; j++) {
            if (current_partitions[j] >= processes[i]) {
                int fragmentation = current_partitions[j] - processes[i];
                if (fragmentation > max_fragmentation) {
                    max_fragmentation = fragmentation;
                    worst_idx = j;
                }
            }
        }

        if (worst_idx != -1) {
            allocated_partitions[i] = worst_idx;
            initial_partition_sizes[i] = current_partitions[worst_idx];
            current_partitions[worst_idx] = 0;
        }
    }

    printf("\n--- Worst Fit Allocation Order ---\n");
    for (int i = 0; i < j_count; i++) {
        if (allocated_partitions[i] != -1) {
            printf("Process %d (%dkB) allocated to Partition %d (Initial: %dkB, Remaining: %dkB)\n", 
                   i + 1, processes[i], 
                   allocated_partitions[i] + 1, 
                   initial_partition_sizes[i], 
                   current_partitions[allocated_partitions[i]]);
        } else {
            printf("Process %d (%dkB) could not be allocated\n", i + 1, processes[i]);
        }
    }
}

int main() {
    int p_count, j_count;
    
    printf("Enter the number of memory partitions: ");
    if (scanf("%d", &p_count) != 1 || p_count <= 0) {
        printf("Invalid input. Exiting.\n");
        return 1;
    }

    int *partitions = (int *)malloc(p_count * sizeof(int));
    if (partitions == NULL) return 1;

    printf("Enter the sizes (in kB) of the %d memory partitions:\n", p_count);
    for (int i = 0; i < p_count; i++) {
        printf("Partition %d size (kB): ", i + 1);
        if (scanf("%d", &partitions[i]) != 1 || partitions[i] <= 0) {
             printf("Invalid input. Exiting.\n");
             free(partitions);
             return 1;
        }
    }

    printf("\nEnter the number of processes: ");
    if (scanf("%d", &j_count) != 1 || j_count <= 0) {
        printf("Invalid input. Exiting.\n");
        free(partitions);
        return 1;
    }
    
    int *processes = (int *)malloc(j_count * sizeof(int));
    if (processes == NULL) {
        free(partitions);
        return 1;
    }

    printf("Enter the sizes (in kB) of the %d processes (in order):\n", j_count);
    for (int i = 0; i < j_count; i++) {
        printf("Process %d size (kB): ", i + 1);
        if (scanf("%d", &processes[i]) != 1 || processes[i] <= 0) {
             printf("Invalid input. Exiting.\n");
             free(partitions);
             free(processes);
             return 1;
        }
    }

    printf("\n\n--- Dynamic Memory Allocation Simulation Results ---\n");
    
    firstFit(partitions, p_count, processes, j_count);
    bestFit(partitions, p_count, processes, j_count);
    worstFit(partitions, p_count, processes, j_count);

    free(partitions);
    free(processes);

    return 0;
}

