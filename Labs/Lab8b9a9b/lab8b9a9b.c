#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <string.h>
#include <fcntl.h>

#define INT_SIZE 4
#define INT_COUNT 10
#define MEMORY_SIZE INT_COUNT * INT_SIZE

int main(){

	int intArray[MEMORY_SIZE];
	signed char *mmapfptr;
	int i, j;
	int sum = 0;
	int mmapfile_fd = open("numbers.bin", O_RDONLY);
	mmapfptr = mmap(0, MEMORY_SIZE, PROT_READ, MAP_PRIVATE, mmapfile_fd, 0);
	for(i = 0; i< INT_COUNT; i++){
		memcpy(intArray + i, mmapfptr + 4*i, INT_SIZE);		
	}
	
	for(j = 0; j < INT_COUNT; j++){
		sum = sum + intArray[j];
	}
	munmap(mmapfptr, MEMORY_SIZE);
	printf("Sum of numbers = %d\n ",sum);
	return 0;
}
