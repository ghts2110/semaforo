#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <dispatch/dispatch.h>

#define NUM_CARROS 5
#define VAGAS 1

dispatch_semaphore_t sem_vagas;

void* carro(void* arg) {
    int id = *(int*)arg;
    printf("Carro %d quer entrar no estacionamento.\n", id);

    dispatch_semaphore_wait(sem_vagas, DISPATCH_TIME_FOREVER);  
    printf("🚗 Carro %d entrou. (vaga ocupada)\n", id);
    sleep(2);  
    printf("⬅️  Carro %d saiu.\n", id);
    dispatch_semaphore_signal(sem_vagas);  

    return NULL;
}

int main() {
    pthread_t threads[NUM_CARROS];
    sem_vagas = dispatch_semaphore_create(VAGAS); 

    for (int i = 0; i < NUM_CARROS; i++) {
        int* id = malloc(sizeof(int));
        *id = i + 1;
        pthread_create(&threads[i], NULL, carro, id);
        sleep(1);  
    }

    for (int i = 0; i < NUM_CARROS; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
