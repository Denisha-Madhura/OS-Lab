#include <stdio.h>
#include <stdbool.h>

#define STUDENTS 5
#define COMPONENTS 3

int main() {
    int max[STUDENTS][COMPONENTS] = {
        {5, 4, 4},
        {4, 3, 3},
        {9, 1, 3},
        {8, 6, 4},
        {2, 2, 3}
    };
    int allocation[STUDENTS][COMPONENTS] = {
        {1, 1, 2},
        {2, 1, 2},
        {3, 0, 1},
        {0, 2, 0},
        {1, 1, 2}
    };
    int total[COMPONENTS] = {10, 7, 8};
    int need[STUDENTS][COMPONENTS];
    int available[COMPONENTS];
    bool finish[STUDENTS] = {false};
    int safeSequence[STUDENTS];
    int count = 0, i, j;

    for (j = 0; j < COMPONENTS; j++) {
        int sum = 0;
        for (i = 0; i < STUDENTS; i++) sum += allocation[i][j];
        available[j] = total[j] - sum;
    }

    for (i = 0; i < STUDENTS; i++)
        for (j = 0; j < COMPONENTS; j++)
            need[i][j] = max[i][j] - allocation[i][j];

    while (count < STUDENTS) {
        bool found = false;
        for (i = 0; i < STUDENTS; i++) {
            if (!finish[i]) {
                bool canAllocate = true;
                for (j = 0; j < COMPONENTS; j++)
                    if (need[i][j] > available[j]) {
                        canAllocate = false;
                        break;
                    }
                if (canAllocate) {
                    for (j = 0; j < COMPONENTS; j++)
                        available[j] += allocation[i][j];
                    safeSequence[count++] = i + 1;
                    finish[i] = true;
                    found = true;
                }
            }
        }
        if (!found) break;
    }

    bool safe = (count == STUDENTS);

    printf("Need Matrix:\n");
    for (i = 0; i < STUDENTS; i++) {
        for (j = 0; j < COMPONENTS; j++)
            printf("%d ", need[i][j]);
        printf("\n");
    }

    if (safe) {
        printf("System is in safe state.\nSafe sequence: ");
        for (i = 0; i < STUDENTS; i++)
            printf("S%d ", safeSequence[i]);
    } else {
        printf("System is in deadlock state.");
    }

    return 0;
}

