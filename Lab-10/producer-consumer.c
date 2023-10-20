/*
Name : Vishnu Teja Surla
Roll : CS21B2037
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5
#define MAX_ITEMS 20

int buffer[BUFFER_SIZE];
int in = 0;
int out = 0;
int produced_count = 0;
int consumed_count = 0;
int item = 0;

sem_t mutex;
sem_t full;
sem_t empty;

void produce_item(){
    item = item + 1;
}

void insert_item(int num){
    buffer[in] = num;
    printf("Produced: %d\n", num);
    in = (in + 1) % BUFFER_SIZE;
}

void consume_item(){
    int received_item = buffer[out];
    printf("Consumed: %d\n", received_item);
    out = (out + 1) % BUFFER_SIZE;
}

void* producer(void* arg) {

   while (produced_count < MAX_ITEMS) {

        produce_item();

        sleep(rand()%2);

        sem_wait(&empty);
        sem_wait(&mutex);

        insert_item(item);

        produced_count++;

        sem_post(&mutex);
        sem_post(&full);
   }

   pthread_exit(NULL);
}

void* consumer(void* arg) {
   while (consumed_count < MAX_ITEMS) {

        sleep(rand()%5);

        sem_wait(&full);
        sem_wait(&mutex);

        consume_item();

        consumed_count++;

        sem_post(&mutex);
        sem_post(&empty);
   }

   pthread_exit(NULL);
}

int main() {
   pthread_t producerThread, consumerThread;

   sem_init(&mutex, 0, 1);
   sem_init(&full, 0, 0);
   sem_init(&empty, 0, BUFFER_SIZE);

   pthread_create(&producerThread, NULL, producer, NULL);
   pthread_create(&consumerThread, NULL, consumer, NULL);

   pthread_join(producerThread, NULL);
   pthread_join(consumerThread, NULL);

   sem_destroy(&mutex);
   sem_destroy(&full);
   sem_destroy(&empty);

   return 0;
}