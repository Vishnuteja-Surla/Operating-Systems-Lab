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
    int fd1;
    char *myfifo = "/tmp/myfile.txt";

    int a, b;

    // Open the named pipe for reading.
    fd1 = open(myfifo, O_RDONLY);

    // Read the integer 'a' from the named pipe.
    read(fd1, &a, sizeof(a));

    // Print the received number 'a'.
    printf("The number received: %d\n", a);

    close(fd1);

    // Calculate the one's complement of 'a'.
    b = ~a;

    // Reopen the named pipe for writing.
    fd1 = open(myfifo, O_WRONLY);

    // Write the one's complement 'b' into the named pipe.
    write(fd1, &b, sizeof(b));

    close(fd1);

    return (0);
}
