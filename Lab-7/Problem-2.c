/*
Name: S. Vishnu Teja
Roll: CS21B2037
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>

#define MAX 100


int main(){

    int pid1, pipe1[2], p1;

    p1 = pipe(pipe1);   // Pipe between Parent and Child

    if(p1 == -1){
        printf("Unable to create pipe 1\n");
        return(-1);
    }

    pid1 = fork();

    if(pid1 < 0){   
        printf("Unable to create a child process\n");
        return(-1);
    }
    // Child Process - Level1
    else if(pid1 == 0){
        int pid2, pipe2[2], p2;

        char str1[MAX], str2[MAX];

        close(pipe1[1]);
        read(pipe1[0], str1, sizeof(str1));

        p2 = pipe(pipe2);   // Pipe between Child and Grandchild

        if(p2 == -1){
            printf("Unable to create pipe 2\n");
            return(-1);
        }

        pid2 = fork();

        if(pid2 < 0){
            printf("Unable to create grand child process\n");
        }
        // Grandchild Process
        else if(pid2 == 0){
            printf("Grandchild Process : Pid = %d and Parent = %d\n", getpid(), getppid());
            char str[MAX];
            close(pipe2[0]);
            printf("Enter the String in Grand Child Process : ");
            fgets(str, MAX, stdin);
            write(pipe2[1], str, sizeof(str));
        }
        // Child Process - Level 2
        else{
            close(pipe2[1]);
            read(pipe2[0], str2, sizeof(str2));
            close(pipe2[0]);
            printf("Child Process : Pid = %d and Parent = %d\n", getpid(), getppid());
            printf("\nParent String : %s\nGrand Child String : %s\n", str1, str2);
            printf("Difference in length = %ld\n", strlen(str1) - strlen(str2));
        }
    }
    // Parent Process
    else{
        printf("Parent Process : Pid = %d and Parent = %d\n", getpid(), getppid());
        char str[MAX];
        close(pipe1[0]);
        printf("Enter the String in Parent Process : ");
        fgets(str, MAX, stdin);
        write(pipe1[1], str, sizeof(str));
        wait(NULL);
    }

    return(0);
}