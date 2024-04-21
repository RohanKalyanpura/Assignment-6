//Rohan Kalyanpura
//homework 6 
//CS 3377.501
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int status;
    int pipes1[2], pipes2[2];
    pipe(pipes1); // ls and grep pipe 
    pipe(pipes2); //  grep and wc pipe 
    
    //Stores the arguments to be used 
    char *ls_args[] = {"ls", "-ltr", NULL};
    char *grep_args[] = {"grep", "3376", NULL};
    char *wc_args[] = {"wc", "-l", NULL};

    //creates first child
    int childpid1 = fork();
    if (childpid1 == 0) {
        // Child 1: Executes ls -ltr
        dup2(pipes1[1], 1); // Redirects the stdout to pipe1 write
        //closes all the parts of the pipes that will not be used
        close(pipes1[0]);
        close(pipes1[1]);
        close(pipes2[0]);
        close(pipes2[1]);
        //executes the program
        execvp(ls_args[0], ls_args);
        //ends the child process
        exit(0);
    }

    int childpid2 = fork();
    if (childpid2 == 0) {
        // Child 2: Executes grep 3376
        dup2(pipes1[0], 0); // Redirects the stdin to pipe1 read
        dup2(pipes2[1], 1); // Redirects the stdout to pipe2 write
        //closes all the parts of the pipes that will not be used
        close(pipes1[0]);
        close(pipes1[1]);
        close(pipes2[0]);
        close(pipes2[1]);
        //executes the program
        execvp(grep_args[0], grep_args);
        //ends the child process
        exit(0);
    }

    // Parent: Executes wc -l
    dup2(pipes2[0], 0); // Redirects the stdin to pipe2 read
    //closes all the parts of the pipes that will not be used
    close(pipes1[0]);
    close(pipes1[1]);
    close(pipes2[0]);
    close(pipes2[1]);
    //executes the program
    execvp(wc_args[0], wc_args);
    //finishes the program
    return 0;
}
