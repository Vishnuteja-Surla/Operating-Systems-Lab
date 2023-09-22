/*
Name: S. Vishnu Teja
Roll: CS21B2037
*/

// Importing Libraries
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<string.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>


#define SHMSIZE 1024


int main(){

    int shmid, key;
    key = 2037;
    char *shm, *s;
    char *msg = "The sun set behind the mountains, casting a warm glow over the tranquil valley below.";

    if((shmid = shmget(key, SHMSIZE, IPC_CREAT | 0666)) < 0){
        printf("Error in creating shared memory\n");
        exit(1);
    }
    if((shm = shmat(shmid, NULL, 0)) == (char *) -1){
        printf("Error in attaching shared memory\n");
        exit(1);
    }
    s = shm;
    for(int i = 0; i < strlen(msg); i++){
        *s++ = msg[i];
    }
    *s = '\0';
    while(*shm != '*'){
        sleep(1);
    }
    for(; *s != '\0'; s++){
        printf("%c", *s);
    }
    printf("\n");

    return(0);
}