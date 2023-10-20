/*
Name : Vishnu Teja Surla
Roll : CS21B2037
*/

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>


typedef struct thread_data{

    int reader;

}thread_data;


sem_t mutex, wrt;

int reader_count = 0;

void *writer_process(void *arg){
    while(1){
        sleep(rand()%3);
        sem_wait(&wrt);
        printf("Writing in Dataset\n");
        sem_post(&wrt);
    }
}

void *reader_process(void *arg){

    while(1){
        sleep(rand()%2);
        sem_wait(&mutex);
        reader_count++;
        if(reader_count == 1){
            sem_wait(&wrt);
        }
        sem_post(&mutex);
        printf("Reader-%ld reading from Dataset\n", (long int)arg+1);
        sem_wait(&mutex);
        reader_count--;
        if(reader_count == 0){
            sem_post(&wrt);
        }
        sem_post(&mutex);
    }
}

int main(){

    pthread_t readerThread[5], writerThread;

    sem_init(&mutex, 0, 1);
    sem_init(&wrt, 0, 1);

    pthread_create(&writerThread, NULL, writer_process, NULL);
    for(long int i=0; i<5; i++){
        pthread_create(&readerThread[i], NULL, reader_process, (void *)i);
    }

    pthread_join(writerThread, NULL);
    for(int i=0; i<5; i++){
        pthread_join(readerThread[i], NULL);
    }

    sem_destroy(&mutex);
    sem_destroy(&wrt);

    return 0;

}