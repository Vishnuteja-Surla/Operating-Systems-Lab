# Question-1

## Write a C program which will create a child process from a parent process. 
In parent process, define one global array and take input from the user.
Perform following operations.

In Parent Process:  
(a) Update the array by subtracting 3 from each element of the array.  
(b) Print the elements, address of the elements and find the minimum element after performing (a).  
(c) Print process id and it’s parent process id

In Child Process:  
(a) Update the global array by adding 2 on each element of the array.  
(b) Print the elements, address of the elements and find the maximum element after performing (a)  
(c) Print process id and it’s parent process id

# Question-2

## Create parent and child processes using fork(). 
In each process, define an array of integer using malloc. 
Before that take the size of the array from the user. 
Insert values in your array (size and array elements may be different for both processes).

In Parent Process:  
(a) Print the array elements and their addresses  
(b) Sort the array and print its values.

In Child Process:  
(a) Print the array elements and their address  
(b) Reverse the array and print its values.

### NOTE: Ensure that first child process should terminate, then Parent Process should start taking input.

# Question-4

## Write two programs (Given Program31.c and Program32.c).

For Program31.c:  
In Parent Process:  
(a) Print your name, roll number, and Institution name   
(b) Print process id and its parent process id and return value of fork() system call.

In Child Process,  
(a) Print id of the process, it’s parent process id, and return value of fork() system call.  
(b) Use exec() system call to execute new program written in Program32.c. 
In Program32.c, write or compute anything of your choice. The executable file for Program32.c is (progam32).  
(c) Write a few printf statements after operation (b)  
Analyze the entire creation of the parent and child processes. Make sure that the parent process terminates after the child process has finished its execution.