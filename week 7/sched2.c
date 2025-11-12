#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t rw_mutex, mutex;
int read_count = 0;

void *reader(void *arg) {
    int f = *((int *)arg);
    sem_wait(&mutex);
    read_count++;
    if (read_count == 1)
        sem_wait(&rw_mutex);
    sem_post(&mutex);

    printf("Reader %d is reading\n", f);
    sleep(1);
    printf("Reader %d finished reading\n", f);

    sem_wait(&mutex);
    read_count--;
    if (read_count == 0)
        sem_post(&rw_mutex);
    sem_post(&mutex);
    pthread_exit(NULL);
}

void *writer(void *arg) {
    int f = *((int *)arg);
    sem_wait(&rw_mutex);

    printf("Writer %d is writing\n", f);
    sleep(2);
    printf("Writer %d finished writing\n", f);

    sem_post(&rw_mutex);
    pthread_exit(NULL);
}

int main() {
    int n_readers, n_writers;

    printf("Enter number of readers: ");
    scanf("%d", &n_readers);
    printf("Enter number of writers: ");
    scanf("%d", &n_writers);

    pthread_t rtid[n_readers], wtid[n_writers];
    int a[n_readers], b[n_writers];
    sem_init(&rw_mutex, 0, 1);
    sem_init(&mutex, 0, 1);

    for (int i = 0; i < n_readers; i++) {
        a[i] = i + 1;
        pthread_create(&rtid[i], NULL, reader, &a[i]);
    }

    for (int i = 0; i < n_writers; i++) {
        b[i] = i + 1;
        pthread_create(&wtid[i], NULL, writer, &b[i]);
    }

    for (int i = 0; i < n_readers; i++)
        pthread_join(rtid[i], NULL);
    for (int i = 0; i < n_writers; i++)
        pthread_join(wtid[i], NULL);

    sem_destroy(&rw_mutex);
    sem_destroy(&mutex);
    return 0;
}

