# Question-1
## Write a program using file handling functions to copy a file (Input1.txt). Write a program which converts entire file (obtained after copying) from lower case to upper case and vice versa.

Don't change the name of the i/p file for your program. Keep it Input1.txt while writing the program.  

# Question-2
## Write a C program to implement First Come First Serve CPU Scheduling Algorithm.

(i) Take input from the user only once (Process_id, Arrival Time, Burst Time) and apply FCFS.

(ii) Your algorithm should work for both scenario: (a) all tasks arrive at the same time (b) tasks may arrive at a different time.

(iii) Compute completion time, turnaround time,  waiting time and response time for each process  for the given input.

(iv) Further compute the average waiting time and average turnaround time.

(v) Print the schedule for the given input.

Note: You can use only integers for process id. Use the linked list implementation for the Queue. 



Output should print like this:

FCFS

P_id      AT     BT   FT   TAT  WT   RT

Avg waiting time:-

Avg turnaround time:-

Testcase 1

P_ID:  1,  2,  3, 4
AT    :  0,  0,  0, 0
BT   :  6,  8,  7,  3

Testcase 2


P_ID:  1, 2, 3, 4, 5, 6
AT:      0, 1, 2, 3, 4, 7
BT:      4, 4, 1, 2, 5, 1