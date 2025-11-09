#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

sem_t mutex, wrt;
int sharevar = 99;
int readcount = 0;

void* reader(void* param) {
    int id = *((int*)param);

    sem_wait(&mutex);
    readcount++;
    if (readcount == 1)
        sem_wait(&wrt); // first reader locks writers
    sem_post(&mutex);

    printf("\nReader %d is reading shared variable = %d", id, sharevar);
    sleep(1);

    sem_wait(&mutex);
    readcount--;
    if (readcount == 0)
        sem_post(&wrt); // last reader releases writer lock
    sem_post(&mutex);

    printf("\nReader %d is done reading", id);
    return NULL;
}

void* writer(void* param) {
    int id = *((int*)param);

    printf("\nWriter %d is trying to enter", id);
    sem_wait(&wrt);

    printf("\nWriter %d has entered critical section", id);
    sharevar++;
    printf("\nWriter %d changed shared variable to %d", id, sharevar);
    sleep(1);

    sem_post(&wrt);
    printf("\nWriter %d is leaving critical section", id);
    return NULL;
}

int main() {
    int n;
    printf("Enter the number of readers/writers (<=5): ");
    scanf("%d", &n);

    pthread_t readers[n], writers[n];
    int ids[n];
    sem_init(&mutex, 0, 1);
    sem_init(&wrt, 0, 1);

    for (int i = 0; i < n; i++) {
        ids[i] = i + 1;
        pthread_create(&writers[i], NULL, writer, &ids[i]);
        pthread_create(&readers[i], NULL, reader, &ids[i]);
    }

    for (int i = 0; i < n; i++) {
        pthread_join(writers[i], NULL);
        pthread_join(readers[i], NULL);
    }

    sem_destroy(&mutex);
    sem_destroy(&wrt);

    printf("\nAll readers and writers have finished.\n");
    return 0;
}

