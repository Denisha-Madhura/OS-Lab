#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void parent_process(int val){
    val++;
    printf("Parent process (PID %d): variable value = %d\n", getpid(),val);
}

void child_process(int val){
    printf("Child process (PID %d): variable value = %d\n", getpid(), val);
}

int main(){
    int common_var = 100;
    pid_t pid = fork();
    if(pid<0){
        perror("fork failed");
        exit(EXIT_FAILURE);
    }else if(pid==0){
        child_process(common_var);
        exit(0);
    }else{
        parent_process(common_var);
        wait(NULL);
    }
    return 0;
}