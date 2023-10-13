/*
Name: S.Vishnu Teja
Roll: CS21B2037
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAT_SIZE 3

int M1[MAT_SIZE][MAT_SIZE], M2[MAT_SIZE][MAT_SIZE];

typedef struct thread_data{

    int A[MAT_SIZE][MAT_SIZE], S[MAT_SIZE][MAT_SIZE], M[MAT_SIZE][MAT_SIZE];

}thread_data;


void *add_matrices(void *arg){

    thread_data *data = (thread_data *)arg;

    for(int i=0; i<MAT_SIZE; i++){
        for(int j=0; j<MAT_SIZE; j++){
            data->A[i][j] = M1[i][j] + M2[i][j];
        }
    }

    pthread_exit(NULL);
}

void *sub_matrices(void *arg){

    thread_data *data = (thread_data *)arg;

    for(int i=0; i<MAT_SIZE; i++){
        for(int j=0; j<MAT_SIZE; j++){
            data->S[i][j] = M1[i][j] - M2[i][j];
        }
    }

    pthread_exit(NULL);
}

void *multiply_matrices(void *arg){

    thread_data *data = (thread_data *)arg;

    for (int i = 0; i < MAT_SIZE; i++) {
        for (int j = 0; j < MAT_SIZE; j++) {
            data->M[i][j] = 0;
            for (int k = 0; k < MAT_SIZE; k++) {
                data->M[i][j] += M1[i][k] * M2[k][j];
            }
        }
    }

    pthread_exit(NULL);
}


int main(){

    pthread_t threads[MAT_SIZE];

    thread_data data;

    printf("Enter the elements of the first matrix:-\n");
    for(int i=0; i<MAT_SIZE; i++){
        for(int j=0; j<MAT_SIZE; j++){
            scanf("%d", &M1[i][j]);
        }
    }

    printf("Enter the elements of the second matrix:-\n");
    for(int i=0; i<MAT_SIZE; i++){
        for(int j=0; j<MAT_SIZE; j++){
            scanf("%d", &M2[i][j]);
        }
    }

    pthread_create(&threads[0], NULL, add_matrices, (void *)&data);
    pthread_create(&threads[1], NULL, sub_matrices, (void *)&data);
    pthread_create(&threads[2], NULL, multiply_matrices, (void *)&data);

    for(int i=0; i<MAT_SIZE; i++){
        pthread_join(threads[i], NULL);
    }

    printf("Matrix M1:-\n");
    for(int i=0; i<MAT_SIZE; i++){
        for(int j=0; j<MAT_SIZE; j++){
            printf("%d\t", M1[i][j]);
        }
        printf("\n");
    }

    printf("Matrix M2:-\n");
    for(int i=0; i<MAT_SIZE; i++){
        for(int j=0; j<MAT_SIZE; j++){
            printf("%d\t", M2[i][j]);
        }
        printf("\n");
    }

    printf("M1 + M2:-\n");
    for(int i=0; i<MAT_SIZE; i++){
        for(int j=0; j<MAT_SIZE; j++){
            printf("%d\t", data.A[i][j]);
        }
        printf("\n");
    }

    printf("M1 - M2:-\n");
    for(int i=0; i<MAT_SIZE; i++){
        for(int j=0; j<MAT_SIZE; j++){
            printf("%d\t", data.S[i][j]);
        }
        printf("\n");
    }

    printf("M1 * M2:-\n");
    for(int i=0; i<MAT_SIZE; i++){
        for(int j=0; j<MAT_SIZE; j++){
            printf("%d\t", data.M[i][j]);
        }
        printf("\n");
    }

    return 0;
}