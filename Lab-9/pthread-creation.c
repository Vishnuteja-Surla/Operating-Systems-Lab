#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 5
#define MAX 1000

int thread_num = 0; // Counter for the current thread number
int sum = 0;       // Variable to store the final sum

// Function to be executed by each thread
void *sum_array(void *arg) {
    thread_num++; // Increment the thread number

    // Calculate the range of numbers to sum for this thread
    int start = (thread_num - 1) * 200 + 1;
    int end = thread_num * 200;

    // Sum the numbers in the given range
    for (int i = start; i <= end; i++) {
        sum += i;
    }
}

int main() {
    pthread_t threads[NUM_THREADS];

    // Create multiple threads
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, sum_array, (void *)NULL);
    }

    // Wait for all threads to finish
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Print the final sum
    printf("Sum of the first %d numbers is %d\n", MAX, sum);

    return 0;
}
