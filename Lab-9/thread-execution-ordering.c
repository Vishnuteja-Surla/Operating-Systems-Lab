/*
Name: S.Vishnu Teja
Roll: CS21B2037
*/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>
#include<pthread.h>


void *thread_A_func(void *arg){

    int *t = (int *)arg;

    printf("Statement-A1\n");
    if(*t==0){
        sleep(1);
    }
    else{
        sleep(2);
    } 
    printf("Statement-A2\n");

    pthread_exit(NULL);
}

void *thread_B_func(void *arg){

    int *t = (int *)arg;

    printf("Statement-B1\n");
    if(*t==0){
        sleep(2);
    }
    else{
        sleep(1);
    } 
    printf("Statement-B2\n");

    pthread_exit(NULL);
}


int main(){
    
    srand(time(NULL));

    pthread_t thread_A, thread_B;

    int r = rand()%2;

    if(r==0){
        int t = rand()%2;
        pthread_create(&thread_A, NULL, thread_A_func, (void *)&t);
        pthread_create(&thread_B, NULL, thread_B_func, (void *)&t);
    }
    else{
        int t = rand()%2;
        pthread_create(&thread_B, NULL, thread_B_func, (void *)&t);
        pthread_create(&thread_A, NULL, thread_A_func, (void *)&t);
    }
    

    pthread_join(thread_A, NULL);
    pthread_join(thread_B, NULL);

    return(0);
}