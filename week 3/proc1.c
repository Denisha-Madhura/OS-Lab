#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(){
    int n,i;
    pid_t pid;
    printf("Enter the numbe of child processes to create: ");
    scanf("%d", &n);
    for(i=0; i<n; i++){
        pid = fork();

        if(pid<0){
            perror("fork failed");
            exit(EXIT_FAILURE);
        }else if(pid == 0){
            printf("Child process %d with PID %d, Parent PID: %d\n", i+1, getpid(), getppid());
            exit(0);
        }
    }
    for(i=0;i<n;i++){
        wait(NULL);
    }

    printf("Parent process PID: %d, created %d children\n", getpid(), n);
    return 0;
}