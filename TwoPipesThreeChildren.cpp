//Rohan Kalyanpura
//homework 6 
//CS 3377.501
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int pipes1[2], pipes2[2];
    pipe(pipes1);
    pipe(pipes2);
    
    //Stores the arguments to be used 
    char *ls_args[] = {"ls", "-ltr", NULL};
    char *grep_args[] = {"grep", "3376", NULL};
    char *wc_args[] = {"wc", "-l", NULL};

    //creates the first child 
    int childpid1 = fork();
    
    if (childpid1 == 0) {
        // Child 1: Executes ls -ltr
        dup2(pipes1[1], 1); // Redirect stdout to pipe1 write
        //close all the unused pipes
        close(pipes1[0]);
        close(pipes1[1]);
        close(pipes2[0]);
        close(pipes2[1]);
        //executes the commands 
        execvp(ls_args[0], ls_args);
        //closes the child process
        exit(0);
    }

    int childpid2 = fork();
    if (childpid2 == 0) {
        // Child 2: Executes grep 3376
        dup2(pipes1[0], 0); // Redirect stdin to pipe1 read
        dup2(pipes2[1], 1); // Redirect stdout to pipe2 write
        //closes the child process
        close(pipes1[0]);
        close(pipes1[1]);
        close(pipes2[0]);
        close(pipes2[1]);
        //executes the commands
        execvp(grep_args[0], grep_args);
        //ends the child process
        exit(0);
    }
    //creates the child process 
    int childpid3 = fork();
    if (childpid3 == 0) {
        // Child 3: Executes wc -l
        dup2(pipes2[0], 0); // Redirect stdin to pipe2 read
        //closes the unused pipes
        close(pipes1[0]);
        close(pipes1[1]);
        close(pipes2[0]);
        close(pipes2[1]);
        //executes the commands
        execvp(wc_args[0], wc_args);
        //ends the third child process
        exit(0);
    }

    // Parent does nothing related to command execution
    //closes more pipes
    close(pipes1[0]);
    close(pipes1[1]);
    close(pipes2[0]);
    close(pipes2[1]);
    wait(NULL); //wait for all children to finish
    //end program
    return 0;
}
