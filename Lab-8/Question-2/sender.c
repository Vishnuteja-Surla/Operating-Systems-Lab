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
#include <sys/stat.h>
#include <fcntl.h>

int main() {
    int fd;
    char *myfifo = "/home/vishnu/Desktop/Sem-5/Operating-System/Labs/Lab-8/Question-2/myfile.txt";

    // Create a named pipe (FIFO) with read and write permissions.
    mkfifo(myfifo, 0666);

    int a, b;

    // Open the named pipe for writing.
    fd = open(myfifo, O_WRONLY);

    // Prompt the user to enter an integer.
    printf("Enter an integer : ");
    scanf("%d", &a);

    // Write the integer 'a' into the named pipe.
    write(fd, &a, sizeof(a));
    close(fd);

    // Reopen the named pipe for reading.
    fd = open(myfifo, O_RDONLY);

    // Read the integer 'b' from the named pipe.
    read(fd, &b, sizeof(b));

    // Print the one's complement of 'a'.
    printf("The ones complement of %d is %d\n", a, b);

    close(fd);

    // Remove (unlink) the named pipe.
    unlink(myfifo);

    return (0);
}
