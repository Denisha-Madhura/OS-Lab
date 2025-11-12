//zombie process 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(){
    pid_t pid = fork();
    if(pid<0){
        perror("fork failed");
        exit(EXIT_FAILURE);
    }else if(pid==0){
        printf("Child process (PID: %d) exiting \n", getpid());
        exit(EXIT_SUCCESS);
    }else{
        printf("Parent process (PID: %d), child PID: %d\n", getpid(), pid);
        printf("Sleeping for 60 seconds, check zombie with ps eaf | grep z \n");
        sleep(60);
        printf("Parent woke up, exiting now \n");
    }

    return 0;
}