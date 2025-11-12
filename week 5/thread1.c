#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

char name[100];
char reg_no[15];

void* print_name(void *args){
    printf("Thread ID: %lu, Name: %s\n", pthread_self(), name);
    return NULL;
}

void* print_regno(void* args){
    printf("Thread ID: %lu, Reg. No. : %s\n", pthread_self(), reg_no);
    return NULL;
}

int main(){
    printf("Enter your name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name,"\n")] = 0;
    printf("Enter your registration number: ");
    fgets(reg_no, sizeof(reg_no), stdin);
    reg_no[strcspn(reg_no, "\n")] = 0;
    pthread_t t1, t2;
    pthread_create(&t1, NULL, print_name, NULL);
    pthread_create(&t2, NULL, print_regno, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2,NULL);
    return 0;
}