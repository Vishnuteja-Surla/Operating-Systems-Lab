/*
Name : S. Vishnu Teja
Roll : CS21B2037
*/

#include<stdio.h>
#include<stdlib.h>

#define MAX 100
int front = -1;
int rear = -1;


struct process {
    int pid;
    int arrival_time;
    int burst_time;
    int completion_time;
    int turn_around_time;
    int waiting_time;
    int response_time;
    int remaining_time;
    int in_queue;
};


void enqueue(struct process *ready, struct process p){
    if(rear == MAX -1){
        printf("Queue is Full\n");
        return;
    }
    if(front == -1){
        front = 0;
    }
    rear++;
    ready[rear] = p;
}

void dequeue(struct process *ready){
    if(front == -1 || front > rear){
        printf("Queue is empty\n");
        return;
    }
    struct process p = ready[front];
    front++;
}

int isempty(){
    if(front == -1 || front > rear){
        return 1;
    }
    return 0;
}


int find_process(struct process p, struct process *disk, int n){
    for(int i=0; i<n; i++){
        if(p.pid == disk[i].pid){
            return i;
        }
    }
}


void compute_values(struct process *p, int n){
    for(int i=0; i<n; i++){
        p[i].turn_around_time = p[i].completion_time - p[i].arrival_time;
        p[i].waiting_time = p[i].turn_around_time - p[i].burst_time;
    }
}


void printlist(struct process* p, int n)
{
    printf("P_id\tAT\tBT\tFT\tTAT\tWT\tRT\n");
    for(int i=0; i<n; i++){
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].arrival_time, p[i].burst_time, p[i].completion_time, p[i].turn_around_time, p[i].waiting_time, p[i].response_time);
    }
}

void print_avgs(struct process *p, int n){
    float avg_tat = 0.0;
    float avg_wt = 0.0;
    float avg_rt = 0.0;
    for(int i=0; i<n; i++){
        avg_tat = avg_tat + p[i].turn_around_time;
        avg_wt = avg_wt + p[i].waiting_time;
        avg_rt = avg_rt + p[i].response_time;
    }
    avg_tat = avg_tat / n;
    avg_wt = avg_wt / n;
    avg_rt = avg_rt / n;
    printf("Average Turn Around Time = %.3f\n", avg_tat);
    printf("Average Waiting Time = %.3f\n", avg_wt);
    printf("Average Response Time = %.3f\n", avg_rt);
}


int main(){

    int n, T;

    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the time quantum: ");
    scanf("%d", &T);
    struct process *p;
    p = (struct process *)malloc(n * sizeof(struct process));

    for(int i=0; i<n; i++){
        printf("Enter the arrival time of process %d: ", i+1);
        scanf("%d", &p[i].arrival_time);
        printf("Enter the burst time of process %d: ", i+1);
        scanf("%d", &p[i].burst_time);
        p[i].pid = i+1;
        p[i].remaining_time = p[i].burst_time;
        p[i].in_queue = 0;
    }

    int time = 0;
    int completed_tasks = 0;
    int context_switches = 0;
    int left_over = 0;
    struct process temp;

    struct process *ready = (struct process *)malloc(MAX * sizeof(struct process));

    while(completed_tasks != n){
        for(int i=0; i<n; i++){
            if(p[i].in_queue == 0 && p[i].arrival_time <= time){
                enqueue(ready, p[i]);
                p[i].in_queue = 1;
            }
        }
        if(left_over){
            enqueue(ready, temp);
            left_over = 0;
        }
        if(isempty()){
            time++;
            continue;
        }
        if(ready[front].remaining_time > T){
            if(ready[front].remaining_time == ready[front].burst_time){
                ready[front].response_time = time - ready[front].arrival_time;
                int pos = find_process(ready[front], p, n);
                p[pos].response_time = ready[front].response_time;
            }
            time = time + T;
            ready[front].remaining_time = ready[front].remaining_time - T;
            left_over = 1;
            temp = ready[front];
            dequeue(ready);
            context_switches++;
        }
        else{
            if(ready[front].remaining_time == ready[front].burst_time){
                ready[front].response_time = time - ready[front].arrival_time;
                int pos = find_process(ready[front], p, n);
                p[pos].response_time = ready[front].response_time;
            }
            time = time + ready[front].remaining_time;
            ready[front].remaining_time = 0;
            ready[front].completion_time = time;
            int pos = find_process(ready[front], p, n);
            p[pos].completion_time = ready[front].completion_time;
            completed_tasks++;
            context_switches++;
            dequeue(ready);
        }
    }
    context_switches--;
    compute_values(p, n);
    printlist(p, n);
    print_avgs(p, n);
    printf("Number of Context Switches = %d\n", context_switches);

    return(0);
}