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

    int pid, pipe1[2], pipe2[2];
    int return1, return2;

    return1 = pipe(pipe1);

    if(return1 == -1){
        printf("Unable to create pipe 1\n");
        return(-1);
    }

    return2 = pipe(pipe2);

    if(return2 == -1){
        printf("Unable to create pipe 2\n");
        return(-1);
    }

    pid = fork();

    if(pid < 0){
        printf("Unable to create a child process\n");
        return(-1);
    }
    else if(pid == 0){

        char string[MAX], reversestring[MAX];

        close(pipe1[1]);
        read(pipe1[0], string, sizeof(string));
        int i = strlen(string) - 1, j = 0;
        while(i >= 0)
            reversestring[j++] = string[i--];
        close(pipe2[0]);
        write(pipe2[1], reversestring, sizeof(reversestring));
    }
    else{

        char string[MAX], reversestring[MAX];

        close(pipe1[0]);
        printf("Parent Process:-\n");
        printf("Enter the string: ");
        scanf("%s", string);
        write(pipe1[1], string, sizeof(string));
        close(pipe2[1]);
        read(pipe2[0], reversestring, sizeof(reversestring));
        printf("The String sent by child : %s\n", reversestring);
        close(pipe2[0]);
    }

    return(0);
}