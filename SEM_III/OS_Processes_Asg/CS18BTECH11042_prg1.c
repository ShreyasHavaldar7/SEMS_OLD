#define _GNU_SOURCE
#include <unistd.h> 
#include <sys/syscall.h> 
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>  
#include <stdlib.h> 
#include <errno.h>   
#include <sys/wait.h> 

//Using linux kernel style indentation

int
main () 
{
    pid_t pid1 = fork(); //Forking a process to create child 1 
    pid_t pid2; 
    int status;

    if(pid1<0) {
        perror("fork");
        exit(1);
    }
    if(pid1>=0) { // On successful creation of Child1
        if(pid1>0) {
            pid2=fork(); // Forking a process to create child 2
            if(pid1<0) {
            perror("fork");
            exit(1);
            }
        }
 
        if (pid1>0 && pid2>0) { // Parent Process

            while(waitpid(-1, &status, 0)!=-1) { // Waiting until both the children terminate
            printf("Child terminates.. PID: %d \n", waitpid(-1, &status, 0));
            }
 
            printf("Parent will now exit.. PID: %d \n", getpid());
            exit(0);
        }
        if(pid1==0) { // Child1
            while(1) {
                printf("Child1 says hello and sleeps for 1s.. PID: %d \n", getpid()); 
                sleep(1);
                printf("After sleeping for 1s.. PID: %d \n", getpid()); 
            }
        }
        if(pid2==0) { //Child2
            printf("Child2 says hi and sleeps for 10s! PID: %d  \n", getpid()); 
            sleep(10);
            printf("Child2 Killing Child1.. PID: %d \n", getpid()); 
            kill(pid1, SIGKILL);
            printf("After killing Child1.. Sleeping for 10s PID: %d \n", getpid()); 
            sleep(10);
            printf("After sleeping for 10s.. PID: %d \n", getpid()); 
            exit(0);
        }
    }
return 0; 
}