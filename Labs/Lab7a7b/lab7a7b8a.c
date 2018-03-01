//Umme Salma
#include <stdio.h>
#include <unistd.h>

#define BUFFER_SIZE 10

#define OFFSET_MASK ‭4095
#define PAGES 1048576
#define OFFSET_BITS 12
#define PAGE_SIZE 4096
/**
Page size = 2^12 = 4096 bits
Number of bits required to represent offset = 12
Number of pages = 2^(32-12) = 1048576
Number of bits required to represent page number = 20
	
**/
int main(void) {
	FILE *fptr = fopen("labaddr.txt", "r");
	char buff[BUFFER_SIZE];
	unsigned int logicalAddress;
	unsigned int pageNumber;
	int offset;
	unsigned int physicalAddress;
	while (fgets(buff, BUFFER_SIZE, fptr) != NULL) {
		// buff is a pointer to each line/address from the file
		logicalAddress = atoi(buff);
		pageNumber = logicalAddress >> OFFSET_BITS;
		offset = logicalAddress & OFFSET_MASK;
		printf("Virtual addr is %d: Page# = %d & Offset = %d. Physical addr = %d\n",
		logicalAddress, pageNumber, offset, physicalAddress);
	}
	
	fclose(fptr);
	return 0;
}
