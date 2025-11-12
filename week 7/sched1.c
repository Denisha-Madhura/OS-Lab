#include <stdio.h>
#include <pthread.h>

int amount = 0;
pthread_mutex_t lock;

void* deposit(void* arg) {
    pthread_mutex_lock(&lock);
    amount += 1000;
    pthread_mutex_unlock(&lock);
    return NULL;
}

void* withdraw(void* arg) {
    pthread_mutex_lock(&lock);
    amount -= 700;
    pthread_mutex_unlock(&lock);
    return NULL;
}

int main() {
    pthread_t x, y;
    pthread_mutex_init(&lock, NULL);
    pthread_create(&x, NULL, deposit, NULL);
    pthread_create(&y, NULL, withdraw, NULL);
    pthread_join(x, NULL);
    pthread_join(y, NULL);
    pthread_mutex_destroy(&lock);
    printf("Final amount: Rs. %d\n", amount);
    return 0;
}

