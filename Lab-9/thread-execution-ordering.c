/*
Name: S.Vishnu Teja
Roll: CS21B2037
*/

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>

sem_t s1, s2;


void *thread_A_func(void *arg){

    sem_wait(&s1);
    printf("Statement-A1\n");
    sem_post(&s2);
    sem_wait(&s1);
    printf("Statement-A2\n");
    sem_post(&s2);

    pthread_exit(NULL);
}

void *thread_B_func(void *arg){

    sem_wait(&s2);
    printf("Statement-B1\n");
    sem_post(&s1);
    sem_wait(&s2);
    printf("Statement-B2\n");
    sem_post(&s1);

    pthread_exit(NULL);
}


int main(){

    sem_init(&s1, 0, 1);
    sem_init(&s2, 0, 1);

    pthread_t thread_A, thread_B;

    pthread_create(&thread_A, NULL, thread_A_func, NULL);
    pthread_create(&thread_B, NULL, thread_B_func, NULL);

    pthread_join(thread_A, NULL);
    pthread_join(thread_B, NULL);

    return(0);
}