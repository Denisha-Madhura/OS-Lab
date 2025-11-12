//how to prevent a zombie function

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
    pid_t pid = fork();
    if(pid<0){
        perror("fork failed");
        error(EXIT_FAILURE);
    }else if(pid==0){
        printf("Child PID: %d exiting\n", getpid());
        exit(EXIT_SUCCESS);
    }else{
        waitpid(pid,NULL,0); //this is the necessary line for the prevention of the creation of a zombie process
        printf("Parent (PID: %d) reaped child (PID: %d). Sleeping for 30 seconds\n", getpid(), pid);
        sleep(30);
        printf("exiting now");
    }

    return 0;
}