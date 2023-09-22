/*
Name: S.Vishnu Teja
Roll: CS21B2037
*/

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
        char *file = "./Exec-Call-test-code";
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