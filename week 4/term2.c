//orphan process

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
    pid_t parent_pid = getpid();
    printf("Original parent pid: %d\n", parent_pid);
    pid_t c1, c2;
    c1 = fork();
    if(c1==0){
        sleep(2);
        printf("Child 1 (not orphan) PID: %d, Parent PID: %d\n", getpid(), getppid());
        exit(0);
    }else{
        c2 = fork();
        if(c2 == 0){
            sleep(5);
            printf("Child 2 (orphan) PID: %d, ParentPID: %d\n", getpid(), getppid());
            exit(0);
        }else{
            sleep(1);
            printf("Parent process terminating, PID: %d\n", getpid());
            waitpid(c1,NULL, 0);
            exit(0);
        }
    }

    return 0;
}