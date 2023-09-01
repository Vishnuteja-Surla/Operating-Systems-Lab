/*
Name: S.Vishnu Teja
Roll: CS21B2037
*/

// Write two programs (Given Program31.c and Program32.c).

// For Program31.c:
// In Parent Process:
// (a) Print your name, roll number, and Institution name 
// (b) Print process id and its parent process id and return value of fork() system call.

// In Child Process,
// (a) Print id of the process, it’s parent process id, and return value of fork() system call.
// (b) Use exec() system call to execute new program written in Program32.c. 
// In Program32.c, write or compute anything of your choice. The executable file for Program32.c is (progam32).
// (c) Write a few printf statements after operation (b).
// Analyze the entire creation of the parent and child processes. Make sure that the parent process terminates after the child process has finished its execution.

#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<string.h>

#define NAME "S.Vishnu Teja"
#define ROLL "CS21B2037"
#define INSTITUTE "IIITDM Kancheepuram"

//Main Function
int main(){

    int pid;
    pid = fork();

    if(pid < 0){
        printf("Error in creating child!\n");
    }
    else if(pid == 0){
        printf("Child Process - PID: %d\n",pid);
        printf("Process Id: %d and Parent Process Id: %d\n", getpid(), getppid());
        char *file = "./Problem-4b";
        execl(file, file, NULL);
        printf("End of child\n");
    }
    else{
        printf("Parent Process - PID: %d\n", pid);
        printf("Name: %s\tRoll Number: %s\tInstitute Name: %s\n", NAME, ROLL, INSTITUTE);
        printf("Process Id: %d and Parent Process Id: %d\n", getpid(), getppid());
    }

    return(0);
}