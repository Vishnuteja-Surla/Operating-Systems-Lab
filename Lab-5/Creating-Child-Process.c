/*
Name : S.Vishnu Teja
Roll: CS21B2037
*/

// Importing the Libraries
#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>


//Print the array function
void printArray(int *arr, int n){
    for(int i=0; i<n; i++){
        printf("Element-%d: %d and Address: %p\n", i+1, arr[i], &arr[i]);
    }
}

// Find maximum
int find_max(int *arr, int n){
    int max = arr[0];
    for(int i=1; i<n; i++){
        if(arr[i] > max){
            max = arr[i];
        }
    }
    return max;
}

// Find minimum
int find_min(int *arr, int n){
    int min = arr[0];
    for(int i=1; i<n; i++){
        if(arr[i] < min){
            min = arr[i];
        }
    }
    return min;
}

// Main Function
int main(){

    int n;
    printf("Enter the number of elements in the array: ");
    scanf("%d", &n);

    int arr[n];
    
    for(int i=0; i<n; i++){
        printf("Enter the element-%d for array : ", i+1);
        scanf("%d", &arr[i]);
    }

    int pid = fork();

    if(pid < 0){
        printf("Error in creating child process\n");
    }
    else if(pid == 0){
        printf("Child Process\n");
        for(int i=0; i<n; i++){
            arr[i] = arr[i] + 2;
        }
        printArray(arr, n);
        printf("Maximum element in the array is: %d\n", find_max(arr, n));
        printf("Process Id: %d and Parent Process Id: %d\n", getpid(), getppid());
    }
    else{
        printf("Parent Process\n");
        for(int i=0; i<n; i++){
            arr[i] = arr[i] - 3;
        }
        printArray(arr, n);
        printf("Minimum element in the array is: %d\n", find_min(arr, n));
        printf("Process Id: %d and Parent Process Id: %d\n", getpid(), getppid());
    }

    return(0);
}