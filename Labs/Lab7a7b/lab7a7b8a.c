//Umme Salma
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 10

#define OFFSET_MASK 4095
#define PAGES 8
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
	int frameNumber;
	unsigned int physicalAddress;
	int page_table[PAGES] = {6,4,3,7,0,1,2,5};
	while (fgets(buff, BUFFER_SIZE, fptr) != NULL) {
		// buff is a pointer to each line/address from the file
		logicalAddress = atoi(buff);
		pageNumber = logicalAddress >> OFFSET_BITS;
		offset = logicalAddress & 4095;
		frameNumber = page_table[pageNumber];
		physicalAddress = (frameNumber << OFFSET_BITS) | offset;
		printf("Virtual addr is %d: Page# = %d & Offset = %d. Physical addr = %d.\n",
		logicalAddress, pageNumber, offset, physicalAddress);
	}
	
	fclose(fptr);
	return 0;
}
