#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <dispatch/dispatch.h>
#include <unistd.h>

#define NUM_CLIENTES 5
#define NUM_CAIXAS 2

dispatch_semaphore_t sem_caixas;

void* cliente(void* arg) {
    int id = *((int*)arg);
    free(arg);

    printf("Cliente %d chegou ao banco.\n", id);

    dispatch_semaphore_wait(sem_caixas, DISPATCH_TIME_FOREVER);

    printf("Cliente %d está sendo atendido...\n", id);
    sleep(rand() % 3 + 1);
    printf("Cliente %d terminou o atendimento.\n", id);

    dispatch_semaphore_signal(sem_caixas);

    return NULL;
}

int main() {
    pthread_t threads[NUM_CLIENTES];
    sem_caixas = dispatch_semaphore_create(NUM_CAIXAS);

    for (int i = 0; i < NUM_CLIENTES; i++) {
        int* id = malloc(sizeof(int));
        *id = i + 1;
        pthread_create(&threads[i], NULL, cliente, id);
        sleep(1);
    }

    for (int i = 0; i < NUM_CLIENTES; i++) {
        pthread_join(threads[i], NULL);
    }

    // dispatch semáforos não precisam ser destruídos manualmente
    return 0;
}
