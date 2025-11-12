#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

int number;

void* check_prime(void* arg){
    int n=number, flag = 0;
    if(n<=1) flag=1;
    else{
        for(int i=2;i*i<=n;i++){
            if(n%i == 0){
                flag = 1;
                break;
            }
        }
    }

    if(flag==0){
        printf("Thread ID: %lu, %d is prime\n", pthread_self(), n);
    }else{
        printf("Thread ID: %lu, %d is not a prime number\n", pthread_self(), n);
    }
}

void* check_oddoreven(void* args){
    int n=number;
    if(n%2==0) printf("Thread ID: %lu, %d is even", pthread_self(), n);
    else printf("Thread ID: %lu %d is odd\n", pthread_self(), n);
}

int main(){
    pthread_t t1, t2;
    printf("Enter a number: ");
    scanf("%d", &number);
    pthread_create(&t1, NULL, check_prime, NULL);
    pthread_create(&t2, NULL, check_oddoreven, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    return 0;
}