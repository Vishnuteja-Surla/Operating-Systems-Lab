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

// Function to calculate one's complement of an integer 'a'.
int ones_complement(int a) {

    int b = 0, p = 1;
    while(a > 0){
        int k = a%2;
        if(k==0){
            b += p;
        }
        p *= 2;
        a /= 2;
    }
    return b;

}

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

    // Calculate the one's complement of 'a' using the ones_complement function.
    b = ones_complement(a);

    // Reopen the named pipe for writing.
    fd1 = open(myfifo, O_WRONLY);

    // Write the one's complement 'b' into the named pipe.
    write(fd1, &b, sizeof(b));

    close(fd1);

    return (0);
}
