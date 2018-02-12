// Umme Salma Gadriwala

#include <pthread.h>
#include <stdio.h>
#include <stdbool.h>
#include <semaphore.h>

#define NUM_THREADS 10

int amount = 0;
pthread_mutex_t mutex;
sem_t depSema;	// deposit semaphore
sem_t withSema;	// withdraw semaphore

void *deposit (void *param);
void *withdraw (void *param);

int main(int argc, char *argv[]) {
	pthread_t tids[NUM_THREADS];
	pthread_attr_t attr;
	
	// take one command line argument
	if (argc != 2) {
		fprintf(stderr, "usage: lab5b6a <int> \n");
		return -1;
	}
	
	if (atoi(argv[1]) != 100) {
		fprintf(stderr, "Amount must be 100\n");
		return -1;
	}
	
	// arg2: number of processes that can share the semaphore
	// arg3: length of queue, account cannot have deposits if value is greater than 4
	if (sem_init(&depSema, 0, 4) != 0) {
		printf("Error in initializing empty semaphore\n");
	}
	if (sem_init(&withSema, 0, 0) != 0) {
		printf("Error in initializing empty semaphore\n");
	}

	// 10 threads: 7 deposit and 3 withdraw
	pthread_attr_init(&attr);
	int i;
	for (i = 0; i < 7; i++) {
		pthread_create(&tids[i], &attr, deposit, argv[1]);
	}
	
	for (i = 7; i < NUM_THREADS; i++) {
		pthread_create(&tids[i], &attr, withdraw, argv[1]);
	}
	
	for (i = 0; i < NUM_THREADS; i++) {
		pthread_join(tids[i], NULL);
	}
	
	printf("Final amount: %d\n", amount);
	return 0;
}

void *deposit(void *param) {
		printf("Executing deposit..\n");
		int d = atoi(param);
		sem_wait(&depSema);
		pthread_mutex_lock(&mutex);
		amount += d;
		pthread_mutex_unlock(&mutex);
		printf("Deposited %d, Amount: %d\n", d, amount);
		sem_post(&withSema);
		pthread_exit(0);
}

void *withdraw(void *param) {
		printf("Executing withdraw..\n");
		int w = atoi(param);
		sem_wait(&withSema);
		pthread_mutex_lock(&mutex);
		amount -= w;
		pthread_mutex_unlock(&mutex);
		printf("Withdrew %d, Amount: %d\n", w, amount);
		sem_post(&depSema);
		pthread_exit(0);
}
