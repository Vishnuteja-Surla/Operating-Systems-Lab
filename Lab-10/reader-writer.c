/*
Name : Vishnu Teja Surla
Roll : CS21B2037
*/

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>


sem_t mutex, wrt;

int reader_count = 0;

void *writer_process(void *arg){
    while(1){
        sleep(rand()%3);
        sem_wait(&wrt);
        printf("Writer-%ld writing into the File\n", (long int)arg+1);
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
        printf("Reader-%ld reading from File\n", (long int)arg+1);
        sem_wait(&mutex);
        reader_count--;
        if(reader_count == 0){
            sem_post(&wrt);
        }
        sem_post(&mutex);
    }
}

int main(){

    int w, r;

    printf("Enter the number of writers : ");
    scanf("%d", &w);
    printf("Enter the number of readers : ");
    scanf("%d", &r);

    pthread_t readerThread[r], writerThread[w];

    sem_init(&mutex, 0, 1);
    sem_init(&wrt, 0, 1);

    
    for(long int i=0; i<w; i++){
        pthread_create(&writerThread[i], NULL, writer_process, (void *)i);
    }
    for(long int i=0; i<r; i++){
        pthread_create(&readerThread[i], NULL, reader_process, (void *)i);
    }

    for(int i=0; i<w; i++){
        pthread_join(writerThread[i], NULL);
    }
    for(int i=0; i<r; i++){
        pthread_join(readerThread[i], NULL);
    }

    sem_destroy(&mutex);
    sem_destroy(&wrt);

    return 0;

}