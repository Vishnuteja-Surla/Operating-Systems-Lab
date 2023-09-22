# Question-1

## Write two different programs (Sender and Receiver) in C to demonstrate IPC using message passing. Process "Sender.c" will take input of atleast 10 numbers and share these numbers with the "Receiver.c" process using message passing. The "Receiver.c" will check each numbers and displays how many odd numbers are there among those numbers and displays them.  

# Question-2

## Write two different programs (Sender and Receiver) in C to demonstrate IPC using FIFO Named Pipe. Process "Sender.c" will write one integer value (Say A) as a message in FIFO. "Receiver.c" will read that message. After reading the message, it will find the one’s complement of A and name it as B1. Then, it will write B on to the pipe. "Sender.c" will read the integer value B1 from the pipe and display it.