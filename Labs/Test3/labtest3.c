// Tasnim Noshin
// Umme Salma Gadriwala

#include <pthread.h>
#include <stdio.h>
#include <stdbool.h>
#include <semaphore.h>
#include <stdlib.h>

#define NUM_THREADS 4

int amount = 0;
pthread_mutex_t mutex;
sem_t mulSema;
sem_t divSema;
sem_t printSema;

void *divides (void *param);
void *multiply (void *param);
void *sum (void *param);
void *print (void *);

typedef struct {
	int one;
	int two;
} parameters;

int main(int argc, char *argv[]) {
	pthread_t tids[NUM_THREADS];
	pthread_attr_t attr;
	
	// take two command line arguments
	if (argc != 3) {
		fprintf(stderr, "usage: labtest3 <int> <int> \n");
		return -1;
	}
	
	if (atoi(argv[1]) >= 100 || atoi(argv[2]) >= 100 || 
	    atoi(argv[1]) % 10 != 0 || atoi(argv[2]) % 10 != 0) {
		fprintf(stderr, "Amounts must be < 100 and a multiple of 10\n");
		return -1;
	}
	
	// arg2: number of processes that can share the semaphore
	// arg3: length of queue, account cannot have deposits if value is greater than 4
	if (sem_init(&mulSema, 0, 0) != 0) {
		printf("Error in initializing empty semaphore\n");
	}
	if (sem_init(&divSema, 0, 0) != 0) {
		printf("Error in initializing empty semaphore\n");
	}
	if (sem_init(&printSema, 0, 0) != 0) {
		printf("Error in initializing empty semaphore\n");
	}
	
	parameters *data = (parameters *) malloc (sizeof(parameters));
	data->one = atoi(argv[1]);
	data->two = atoi(argv[2]);
	
	pthread_t t1; //thread 1
	pthread_t t2; //thread 2
	pthread_t t3; //thread 3
	pthread_t t4; //thread 4

	// 2 threads
	pthread_attr_init(&attr);
	
	pthread_create(&t1, &attr, divides, data);
	pthread_create(&t2, &attr, multiply, data);
	
	pthread_create(&t3, &attr, sum, data);
	pthread_create(&t4, &attr, print, NULL);
	
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	pthread_join(t3, NULL);
	pthread_join(t4, NULL);
	free(data);
	
	printf("End of Main!\n");
	return 0;
}

void *divides(void *param) {
		pthread_mutex_lock(&mutex);
		parameters *p = param;
		int one = p->one;
		int two = p->two;
		p->one = one/10;
		p->two = two/10;
		printf("divides returns: %d, %d\n", p->one, p->two);
		pthread_mutex_unlock(&mutex);
		sem_post(&divSema);
		pthread_exit(0);
}

void *multiply(void *param) {
		pthread_mutex_lock(&mutex);
		parameters *p = param;
		int one = p->one;
		int two = p->two;
		p->one = one*5;
		p->two = two*5;
		printf("multiply returns: %d, %d\n", p->one, p->two);
		pthread_mutex_unlock(&mutex);
		sem_post(&mulSema);
		pthread_exit(0);
}

void *sum(void *param) {
		sem_wait(&mulSema);
		sem_wait(&divSema);
		parameters *p = param;
		int one = p->one;
		int two = p->two;
		printf("sum returns: %d\n", one+two);
		sem_post(&printSema);
		pthread_exit(0);
}

void *print(void *param) {
		sem_wait(&printSema);
		printf("I am the last thread!\n");
		pthread_exit(0);
}
