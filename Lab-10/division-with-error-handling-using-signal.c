    /*
    Name : Vishnu Teja Surla
    Roll : CS21B2037
    */

    #include<stdio.h>
    #include<signal.h>
    #include<stdlib.h>
    #include<unistd.h>
    #include<sys/wait.h>
    #include<sys/types.h>


    void zero_division_signal(int sig){
        printf("Error : Division by zero\n");
        exit(1);
    }

    void fork_error_signal(int sig){
        printf("Error : Fork failed\n");
        exit(0);
    }


    int main(){

        int pid;

        pid = fork();

        signal(SIGFPE, zero_division_signal);

        if(pid > 0){
            wait(NULL);
            printf("Parent Process\n");
            // Parent Process
            int A[8] = {2, 1, 3, 0, 5, 0, 7, 9};
            int num;
            printf("Enter a number : ");
            scanf("%d", &num);
            for(int i = 0; i < 8; i++){\
                printf("%d / %d = %d\n", num, A[i], num%A[i]);
            }
        }
        else if(pid == 0){
            // Child Process
            printf("Child Process\n");
            int num;
            srand(getpid());
            int i = 0;
            while(1){
                i++;
                num = rand()%21 + 10;
                printf("Random Number-%d : %d\n", i, num);
                if(num > 20){
                    exit(0);
                }
            }

        }
        else{
            // Error
            signal(SIGUSR1, fork_error_signal);
            raise(SIGUSR1);
        }

        return(0);
    }