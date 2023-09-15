/*
Name : S. Vishnu Teja
Roll : CS21B2037
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>

#define MAX_SIZE 100

// Define a structure to hold the message data.
struct message {
    long int msg_type;  // Message type used for message queue.
    int numbers[MAX_SIZE];  // Array to hold integer numbers.
};
typedef struct message message;

int main() {
    int msg_id, n;
    message msg1;

    // Prompt the user to enter the number of inputs.
    printf("Enter the number of inputs (At least 10): ");
    scanf("%d", &n);

    // Check if the input is valid (at least 10).
    if (n < 10) {
        printf("INVALID INPUT\n");
        return (-1);  // Exit the program with an error code.
    }

    int num[n];

    // Create or get a message queue with a key of 12345 and read/write permissions.
    msg_id = msgget((key_t)12345, 0666 | IPC_CREAT);

    // Check if message queue creation was successful.
    if (msg_id == -1) {
        printf("Error in creating queue\n");
        exit(-1);  // Exit the program with an error code.
    }

    // Prompt the user to enter 'n' integer values.
    for (int i = 0; i < n; i++) {
        printf("Enter an integer: ");
        scanf("%d", &num[i]);
    }

    // Prepare the message structure.
    msg1.msg_type = 1;  // Set the message type.
    msg1.numbers[0] = n;  // Store the number of integers as the first element.
    for (int i = 0; i < n; i++) {
        msg1.numbers[i + 1] = num[i];  // Store the integer values in the message.
    }

    // Send the message to the message queue.
    if (msgsnd(msg_id, (void *)&msg1, MAX_SIZE * sizeof(int), 0) == -1) {
        printf("Message not sent\n");
    }

    return 0;  // Exit the program successfully.
}
