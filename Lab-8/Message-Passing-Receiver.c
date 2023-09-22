/*
Name: S. Vishnu Teja
Roll: CS21B2037
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MAX_SIZE 100

// Define a structure to hold the received message.
struct message {
    long int msg_type; // Message type used for the message queue.
    int numbers[MAX_SIZE]; // Array to hold integer numbers.
};
typedef struct message message;

int main() {
    int msg_id, odd_count = 0; // Initialize message queue ID and count of odd numbers.
    message msg1; // Declare a message structure to store received data.
    long int msg_to_receive = 1; // Message type to receive.

    // Get the message queue with key 12345 and read permissions.
    msg_id = msgget((key_t)12345, 0644);

    // Receive a message from the message queue with the specified message type.
    msgrcv(msg_id, (void *)&msg1, MAX_SIZE * sizeof(int), msg_to_receive, 0);

    printf("The Numbers are: ");

    // Print the received numbers.
    for (int i = 1; i <= msg1.numbers[0]; i++) {
        printf("%d  ", msg1.numbers[i]);
    }
    printf("\n");
    printf("The odd numbers are: ");

    // Iterate through the received numbers to find and print odd numbers.
    for (int i = 1; i <= msg1.numbers[0]; i++) {
        if (msg1.numbers[i] % 2 != 0) {
            printf("%d  ", msg1.numbers[i]);
            odd_count++;
        }
    }

    // Print the count of odd numbers.
    printf("\nThe Number of odd numbers is %d\n", odd_count);

    // Remove the message queue.
    msgctl(msg_id, IPC_RMID, 0);

    return (0);
}
