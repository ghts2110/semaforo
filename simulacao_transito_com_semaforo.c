#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>
#include <semaphore.h>
#include <dispatch/dispatch.h>

char rua1[4] = {' ', ' ', ' ', ' '};
char rua2[4] = {' ', ' ', ' ', ' '};
char compartilhado = ' ';

pthread_mutex_t mutex;
sem_t semaforo_cruzamento;

int semaforo_rua1 = 1;
int semaforo_rua2 = 0;

void print_ruas() {
    system("clear");
    printf("\n\n");
    printf("             rua 1\n");
    printf("           +     +\n");
    printf("           |  %c  |\n", rua1[0]);
    printf("           +-----+\n");
    printf("           |  %c  |\n", rua1[1]);
    printf("      +-+--+\033[32m-----\033[39m+--+-+\n");
    printf("rua 4 %c | %c\033[31m|\033[39m  %c  |%c | %c  rua 2\n", rua2[0], rua2[1], compartilhado, rua2[2], rua2[3]);
    printf("      +-+--+-----+--+-+\n");
    printf("           |  %c  |\n", rua1[2]);
    printf("           +-----+\n");
    printf("           |  %c  |\n", rua1[3]);
    printf("           +     +\n");
    printf("             rua 3\n\n\n");
}

void *carro_rua1(void *arg) {
    char carro = 'A';
    while (1) {
        for (int i = 0; i <= 4; i++) {
            pthread_mutex_lock(&mutex);

            if (i == 2 && !semaforo_rua1) {
                pthread_mutex_unlock(&mutex);
                usleep(300000);
                i--; 
                continue;
            }

            if (i == 2) {
                pthread_mutex_unlock(&mutex);
                sem_wait(&semaforo_cruzamento); 
                pthread_mutex_lock(&mutex);
            }

            if(i == 0){
                rua1[3] = ' ';
                rua1[i] = carro;
            }else if(i == 1){
                rua1[i-1] = ' ';
                rua1[i] = carro;
            }else if(i == 2){
                rua1[i - 1] = ' ';
                compartilhado = carro;
            } else if (i == 3) {
                compartilhado = ' ';
                rua1[i-1] = carro;
                sem_post(&semaforo_cruzamento);
            } else if (i == 4){
                rua1[i-2] = ' ';
                rua1[i-1] = carro;
            }

            print_ruas();
            pthread_mutex_unlock(&mutex);
            usleep(300000);
        }
    }
    return NULL;
}

void *carro_rua2(void *arg) {
    char carro = 'B';
    while (1) {
        for (int i = 0; i <= 4; i++) {
            pthread_mutex_lock(&mutex);

            if (i == 2 && !semaforo_rua2) {
                pthread_mutex_unlock(&mutex);
                usleep(300000);
                i--;
                continue;
            }

            if (i == 2) {
                pthread_mutex_unlock(&mutex); 
                sem_wait(&semaforo_cruzamento); 
                pthread_mutex_lock(&mutex);
            }


            if(i == 0){
                rua2[3] = ' ';
                rua2[i] = carro;
            }else if(i == 1){
                rua2[i-1] = ' ';
                rua2[i] = carro;
            }else if(i == 2){
                rua2[i - 1] = ' ';
                compartilhado = carro;
            } else if (i == 3) {
                compartilhado = ' ';
                rua2[i-1] = carro;
                sem_post(&semaforo_cruzamento);
            } else if (i == 4){
                rua2[i-2] = ' ';
                rua2[i-1] = carro;
            }

            print_ruas();
            pthread_mutex_unlock(&mutex);
            usleep(300000);
        }
    }
    return NULL;
}


int main() {
    pthread_t carro1_thread, carro2_thread;

    pthread_mutex_init(&mutex, NULL);
    sem_init(&semaforo_cruzamento, 0, 1);

    pthread_create(&carro1_thread, NULL, carro_rua1, NULL);
    pthread_create(&carro2_thread, NULL, carro_rua2, NULL);

    while (1) {
        sleep(5);
        pthread_mutex_lock(&mutex);
        semaforo_rua1 = !semaforo_rua1;
        semaforo_rua2 = !semaforo_rua2;
        pthread_mutex_unlock(&mutex);
    }

    pthread_join(carro1_thread, NULL);
    pthread_join(carro2_thread, NULL);
    return 0;
}