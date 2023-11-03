/*
Name: S. Vishnu Teja
Roll: CS21B2037
*/


/*
Implement the dining philosopher's problem’s solution using semaphore. 
Your solution should allow two philosopher's to eat simultaneously if there are five philosophers thread running simultaneously. 
Also, clearly define the eating task and thinking task inside the respective functions.
*/

// Including Libraries

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>

// Declaring Macros

#define N 5     // Number of philosophers and Chopsticks
#define EATING 0   // EATING = 0 is a state of philosopher
#define THINKING 1 // THINKING = 1 is a state of philosopher
#define HUNGRY 2   // HUNGRY = 2 is a state of philosopher

// Declaring Global Variables
sem_t phil[N]; // Declaring Philosophores as a semaphore
sem_t mutex;        // Declaring mutex as a semaphore
int state[N];       // Declaring state of philosophers as an array


// Declaring Functions

void check_neighbours(int num){
    // Checking if the neighbours are not eating and if so, then changing state to EATING
    if(state[num] == HUNGRY && 
    state[(num+1)%N] != EATING && 
    state[(num+N-1)%N] != EATING){
        state[num] = EATING;
        printf("Philosopher-%d is eating\n", num+1);
        sem_post(&phil[num]); // Waking the Philosopher to eat
    }

}

void *philosopher(void *arg){
    while(1){
        long int num = (long int)arg; // Converting argument to integer
        sleep(1);  // Thinking for some time
        
        state[num] = HUNGRY;    // Changing state to HUNGRY
        printf("Philosopher-%ld is hungry\n", num+1);
        
        sem_wait(&mutex);   // Acquiring mutex to pickup fork
        check_neighbours(num);  // Checking if neighbours are not eating and wake him if not
        sem_post(&mutex);   // Releasing mutex to so that other philosophers can pickup fork
        
        sem_wait(&phil[num]);   // If not able to eat, then wait until woken up by neighbours
        sleep(1);   // Eating for some time

        sem_wait(&mutex);   // Acquiring mutex to putdown fork
        state[num] = THINKING;  // Changing state to THINKING
        printf("Philosopher-%ld is putting down the forks\n", num+1);
        printf("Philosopher-%ld is thinking\n", num+1);
        check_neighbours((num+N-1)%N);  // Checking if left neighbour can eat
        check_neighbours((num+1)%N);    // Checking if right neighbour can eat
        sem_post(&mutex);   // Releasing mutex to so that other philosophers can putdown fork
    }
}


// Main Function

int main(){

    // Step-1: Initializing Philosopher's semaphores to 1 i.e, Ready to Eat
    for(int i=0; i<N; i++){
        sem_init(&phil[i], 0, 1);
    }

    // Step-2: Initializing mutex semaphore to 1 so as to ensure only one philosopher can change state at a time
    sem_init(&mutex, 0, 1);

    // Step-3: Creating a thread for each philosopher
    pthread_t philosophers[N];
    for(long int i=0; i<N; i++){
        state[i] = THINKING;    // Initializing state of each philosopher to THINKING
        pthread_create(&philosophers[i], NULL, philosopher, (void *)i);
        printf("Philosopher-%ld is thinking\n", i+1);
    }

    // Step-4: Joining all the threads
    for(int i=0; i<N; i++){
        pthread_join(philosophers[i], NULL);
    }

    return(0);
}