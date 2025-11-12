#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

void create_process_tree(int depth, int children){
    if(depth<=0) return;
    for(int i=0;i<children;i++){
        pid_t pid = fork();
        if(pid<0){
            perror("fork failed");
        }else if(pid == 0){
            printf("Process PID: %d, Parent PID: %d, Depth: %d\n", getpid(), getppid(), depth);
            create_process_tree(depth-1, children);
            exit(0);
        }
    }

    for(int i=0;i<children;i++){
        wait(NULL);
    }
}
    
int main(){
    int depth, children;
    printf("Enter the depth of process tree: ");
    scanf("%d", &depth);
    printf("Enter no. of children per process");
    scanf("%d", &children);
    printf("Root process PID: %d\n", getpid());
    return 0;
}
