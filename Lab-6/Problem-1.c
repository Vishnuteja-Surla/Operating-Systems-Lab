/*
Name: S.Vishnu Teja
Roll: CS21B2037
*/

//Importing Libraries
#include<stdio.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<unistd.h>


int main(){

    int pid[4];
    pid[0] = fork();

    if(pid[0] == 0){
        printf("Child 1 My Id is %d and my parent id is %d\n", getpid(), getppid());
    }
    else if(pid[0] > 0){
        pid[1] = fork();
        if(pid[1] == 0){
            
            pid[2] = fork();
            if(pid[2] == 0){
                printf("Child 3 My Id is %d and my parent id is %d\n", getpid(), getppid());
            }
            else if(pid[2] > 0){
                pid[3] = fork();
                if(pid[3] == 0){
                    printf("Child 4 My Id is %d and my parent id is %d\n", getpid(), getppid());
                }
                else if(pid[3] > 0){
                    wait(NULL);
                    wait(NULL);
                    printf("Child 2 My Id is %d and my parent id is %d\n", getpid(), getppid());
                }
                else{
                    printf("Error in creating child process\n");
                }
            }
        }
        else if(pid[1] > 0){
            wait(NULL);
            wait(NULL);
            printf("Parent process my id is %d and my parent id is %d\n", getpid(), getppid());
        }
        else{
            printf("Error in creating child process\n");
        }
    }
    else{
        printf("Error in creating child process\n");
    }

    return(0);
}