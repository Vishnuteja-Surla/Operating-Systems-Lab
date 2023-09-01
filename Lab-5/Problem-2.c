/*
Name: S.Vishnu Teja
Roll: CS21B2037
*/

/*
Create parent and child processes using fork(). 
In each process, define an array of integer using malloc. 
Before that take the size of the array from the user. 
Insert values in your array (size and array elements may be different for both processes).

In Parent Process:
(a) Print the array elements and their addresses
(b) Sort the array and print its values.

In Child Process:
(a) Print the array elements and their address
(b) Reverse the array and print its values.

NOTE: Ensure that first child process should terminate, then Parent Process should start taking input.
*/

//Importing the Libraries
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>

//Print the array function
void printArray(int *arr, int n){
    for(int i=0; i<n; i++){
        printf("Element-%d: %d and Address: %p\n", i+1, arr[i], &arr[i]);
    }
}

//Reverse the array function
void reverseArray(int *arr, int n){
    int temp;
    for(int i=0; i<n/2; i++){
        temp = arr[i];
        arr[i] = arr[n-i-1];
        arr[n-i-1] = temp;
    }
    printf("Reversed Array:\n");
    printArray(arr, n);
}

//Sort the array function
void sortedArray(int *arr, int n){
    int temp;
    for(int i=0; i<n; i++){
        for(int j=i+1; j<n; j++){
            if(arr[j] < arr[i]){
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
    printf("Sorted Array:\n");
    printArray(arr, n);
}

//Main Function
int main(){

    int n;

    int pid = fork();

    if(pid < 0){
        printf("Error in creating child process\n");
    }
    else if(pid == 0){
        printf("Child Process\n");
        
        printf("Enter the number of elements in the array : ");
        scanf("%d",&n);
        int *arr = (int *)malloc(n*sizeof(int));
        for(int i=0; i<n; i++){
            printf("Enter the element-%d for array : ", i+1);
            scanf("%d", &arr[i]);
        }
        printArray(arr, n);
        reverseArray(arr, n);
    }
    else{
        wait(NULL);
        printf("Parent Process\n");

        printf("Enter the number of elements in the array : ");
        scanf("%d",&n);
        int *arr = (int *)malloc(n*sizeof(int));
        for(int i=0; i<n; i++){
            printf("Enter the element-%d for array : ", i+1);
            scanf("%d", &arr[i]);
        }
        printArray(arr, n);
        sortedArray(arr, n);
    }

    return(0);
}