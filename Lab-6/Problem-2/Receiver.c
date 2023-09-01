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
    char *msg = "She smiled, her eyes twinkling with mischief, as she plotted her next adventure.";

    if((shmid = shmget(key, SHMSIZE, 0666)) < 0){
        printf("Error in shmget\n");
        exit(1);
    }
    if((shm = shmat(shmid, NULL, 0)) == (char *) -1){
        printf("Error in attaching shared memory\n");
        exit(1);
    }
    for(s = shm; *s != '\0'; s++){
        printf("%c", *s);
    }
    printf("\n");
    *shm = '*';
    for(int i = 0; i < strlen(msg); i++){
        *s++ = msg[i];
    }
    *s = '\0';
    return(0);
}