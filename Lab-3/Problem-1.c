/*
Name : S.Vishnu Teja
Roll : CS21B2037
*/

// Write a C program to implement the Shortest Job First Scheduling Algorithm.

// (i) Take input from the user only once (Process_id, Arrival Time, Burst Time) and apply SJF.

// (ii) Your algorithm should work for both scenarios: 
// (a) all tasks arrive at the same time (b) tasks may arrive at a different time.

// (iii) Compute completion time, turnaround time,  waiting time and response time for each process  for the given input.

// (iv) Further compute the average waiting time and average turnaround time.

// (v) Print the schedule for the given input.

// Note: You can use only integers for process id. Use the min heap data structure (using linked list) to implement SJF Queue.



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
    int in_queue;
    struct process *next;
};

void copy_node(struct process *p1, struct process *p2){
    p1->pid = p2->pid;
    p1->arrival_time = p2->arrival_time;
    p1->burst_time = p2->burst_time;
    p1->finish_time = p2->finish_time;
    p1->turn_around_time = p2->turn_around_time;
    p1->waiting_time = p2->waiting_time;
    p1->response_time = p2->response_time;
    p1->in_queue = p2->in_queue;
    p1->next = NULL;
}

struct process *create_process(int id, int at, int bt){
    
    struct process* temp = (struct process*)malloc(sizeof(struct process));
    
    temp->pid = id;
    temp->arrival_time = at;
    temp->burst_time = bt;
    temp->next = NULL;

    return temp;
}


struct process *insert(struct process *head, struct process *temp){
    
    if(head == NULL){
        head = temp;
    }
    else{
        struct process *temp1 = head;
        while(temp1->next != NULL){
            temp1 = temp1->next;
        }
        temp1->next = temp;
    }
    return head;
}


void printlist(struct process* head)
{
    struct process *temp = head;
    printf("P_id\tAT\tBT\tFT\tTAT\tWT\tRT\n");
    while (temp != NULL) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", temp->pid, temp->arrival_time, temp->burst_time, temp->finish_time, temp->turn_around_time, temp->waiting_time, temp->response_time);
        temp = temp->next;
    }
}


// void swap_processs(struct process *p1, struct process *p2){
//     int temp = p1->pid;
//     p1->pid = p2->pid;
//     p2->pid = temp;

//     temp = p1->arrival_time;
//     p1->arrival_time = p2->arrival_time;
//     p2->arrival_time = temp;

//     temp = p1->burst_time;
//     p1->burst_time = p2->burst_time;
//     p2->burst_time = temp;
// }


// void heapify(struct process *head, int i, int n) {
//     struct process *current = head;
//     struct process *smallest = current;
//     int l = 2 * i + 1;
//     int r = 2 * i + 2;

//     for (int j = 0; j < i; j++) {
//         current = current->next;
//     }

//     if (l < n) {
//         struct process *left = current;
//         for (int j = 0; j < l; j++) {
//             left = left->next;
//         }
//         if (left->burst_time < current->burst_time) {
//             smallest = left;
//         }
//     }

//     if (r < n) {
//         struct process *right = current;
//         for (int j = 0; j < r; j++) {
//             right = right->next;
//         }
//         if (right->burst_time < smallest->burst_time) {
//             smallest = right;
//         }
//     }

//     if (smallest != current) {
//         swap_processs(current, smallest);
//         heapify(head, i, n);
//     }
// }

// void build_heap(struct process *head, int n) {
//     for (int i = n / 2 - 1; i >= 0; i--) {
//         heapify(head, i, n);
//     }
// }

struct process* swap(struct process* ptr1, struct process* ptr2)
{
    struct process* tmp = ptr2->next;
    ptr2->next = ptr1;
    ptr1->next = tmp;
    return ptr2;
}
 
/* Function to sort the list */
int bubbleSort(struct process** head, int count)
{
    struct process** h;
    int i, j, swapped;
 
    for (i = 0; i <= count; i++) {
 
        h = head;
        swapped = 0;
 
        for (j = 0; j < count - i - 1; j++) {
 
            struct process* p1 = *h;
            struct process* p2 = p1->next;
 
            if (p1->burst_time > p2->burst_time) {
 
                /* update the link after swapping */
                *h = swap(p1, p2);
                swapped = 1;
            }
 
            h = &(*h)->next;
        }
 
        /* break if the loop ended without any swap */
        if (swapped == 0)
            break;
    }

}

int getCount(struct process* head)
{
    int count = 0; // Initialize count
    struct process* current = head; // Initialize current
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}


void compute_data(struct process *temp){

    temp->turn_around_time = temp->finish_time - temp->arrival_time;
    temp->waiting_time = temp->turn_around_time - temp->burst_time;
    temp->response_time = temp->waiting_time;
}


int main(){

    struct process *head = NULL;

    int n;
    printf("Enter the number of processes : ");
    scanf("%d",&n);

    struct process *output = NULL;
    
    struct process disk[n];
    for(int i=0; i<n; i++){
        int id, at, bt;
        printf("Enter the process id, arrival time and burst time : ");
        disk[i].in_queue = 0;
        scanf("%d %d %d",&disk[i].pid, &disk[i].arrival_time, &disk[i].burst_time);
    }

    int time = 0;
    float avg_waiting_time = 0.0;
    float avg_turn_around_time = 0.0;
    int count = 0;

    while(count < n){
        
        for(int i=0; i<n; i++){
            if(disk[i].arrival_time <= time && disk[i].in_queue == 0){
                struct process *temp = create_process(disk[i].pid, disk[i].arrival_time, disk[i].burst_time);
                head = insert(head, temp);
                disk[i].in_queue = 1;
            }
        }

        if(head == NULL){
            time++;
            continue;
        }

        // build_heap(head, n);
        bubbleSort(&head, getCount(head));

        time += head->burst_time;

        head->finish_time = time;
        compute_data(head);
        avg_turn_around_time += head->turn_around_time;
        avg_waiting_time += head->waiting_time;
        struct process *p = create_process(head->pid, head->arrival_time, head->burst_time);
        copy_node(p, head);
        output = insert(output, p);
        struct process *temp = head;
        head = head->next;
        temp = NULL;
        count += 1;

    }

    avg_turn_around_time = avg_turn_around_time/n;
    avg_waiting_time = avg_waiting_time/n;
    printlist(output);
    printf("Avg Waiting time : %.3f\n",avg_waiting_time);
    printf("Avg Turn Around Time : %.3f\n", avg_turn_around_time);

    return(0);
}