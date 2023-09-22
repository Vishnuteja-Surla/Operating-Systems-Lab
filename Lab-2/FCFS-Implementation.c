// Write a C program to implement First Come First Serve CPU Scheduling Algorithm.

// (i) Take input from the user only once (Process_id, Arrival Time, Burst Time) and apply FCFS.

// // (ii) Your algorithm should work for both scenario: 
// (a) all tasks arrive at the same time (b) tasks may arrive at a different time.

// (iii) Compute completion time, turnaround time,  waiting time and response time for each process  for the given input.

// (iv) Further compute the average waiting time and average turnaround time.

// (v) Print the schedule for the given input.



#include<stdio.h>
#include<stdlib.h>

struct process{
    int pid;
    int arrival_time;
    int burst_time;
    int finish_time;
    int turn_around_time;
    int waiting_time;
    int response_time;
    struct process *next;
};


struct process *head = NULL;


struct process *create_node(int id, int at, int bt){
    
    struct process* temp = (struct process*)malloc(sizeof(struct process));
    
    temp->pid = id;
    temp->arrival_time = at;
    temp->burst_time = bt;
    temp->next = NULL;

    return temp;
}

void printlist(struct process* head)
{
    printf("P_id\tAT\tBT\tFT\tTAT\tWT\tRT\n");
    while (head != NULL) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", head->pid, head->arrival_time, head->burst_time, head->finish_time, head->turn_around_time, head->waiting_time, head->response_time);
        head = head->next;
    }
}

void compute_data(int n){
    struct process *temp = head;
    int current_time = temp->arrival_time;
    float avg_waiting_time = 0.0;
    float avg_turn_around_time = 0.0;

    for(int i=0; i<n; i++){
        current_time += temp->burst_time;
        temp->finish_time = current_time;
        temp->turn_around_time = temp->finish_time - temp->arrival_time;
        avg_turn_around_time += temp->turn_around_time;
        temp->waiting_time = temp->turn_around_time - temp->burst_time;
        avg_waiting_time += temp->waiting_time;
        temp->response_time = temp->waiting_time;
        temp = temp->next;
    }
    avg_turn_around_time = avg_turn_around_time/n;
    avg_waiting_time = avg_waiting_time/n;
    printlist(head);
    printf("Avg Waiting time : %.3f\n",avg_waiting_time);
    printf("Avg Turn Around Time : %.3f\n", avg_turn_around_time);
}


int main(){
    
    int n, id, at, bt;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct process *newprocess;
    struct process *last = NULL;

    for(int i=0; i<n; i++){
        id = i+1;
        printf("Enter Process-%d Arrival Time : ", i+1);
        scanf("%d", &at);
        printf("Enter Process-%d Burst Time : ", i+1);
        scanf("%d", &bt);
        newprocess = create_node(id, at, bt);
        if(head == NULL){
            head = newprocess;
            last = newprocess;
        }
        else{
            last->next = newprocess;
            last = newprocess;
        }
    }

    compute_data(n);
}