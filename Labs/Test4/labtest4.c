// Tasnim Noshin
// Umme Salma Gadriwala

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/mman.h> /*for mmap() function*/
#include <string.h> /*for memcpy function*/
#include <fcntl.h> /*for file descriptors*/

#define BUFFER_SIZE 10

#define OFFSET_MASK 255
#define PAGES 256
#define OFFSET_BITS 8
#define PAGE_SIZE 256
#define PAGE_TABLE_SIZE 256

int main(void) {
	int i = 0;
	
	int pageNumber;
	int offset;
	int logicalAddress;
	int physicalAddress;
	int frameNumber;
	int page_table[PAGES];
	
	int pt = open("page_table.bin", O_RDONLY);
    if(pt < 0) return 1; // if file is not correctly opened
    	// map BACKING_STORE to a memory region
    signed char *mmapfptr = mmap(0, PAGE_TABLE_SIZE, PROT_READ, MAP_PRIVATE, pt, 0);
    close(pt);

    for (i = 0; i < PAGES; i++) {
    	memcpy(page_table + i, mmapfptr + (i*4), 4);
    }
	
	FILE *fptr = fopen("ltaddr.txt", "r");
	char buff[BUFFER_SIZE]; // for reading from file
	
	while (fgets(buff, BUFFER_SIZE, fptr) != NULL) {
		logicalAddress = atoi(buff);
		pageNumber = logicalAddress >> OFFSET_BITS;
		offset = logicalAddress & OFFSET_MASK;
		frameNumber = page_table[pageNumber];
		physicalAddress = (frameNumber << OFFSET_BITS) | offset;
		printf("Virtual address: %d Page#:%d Offset:%d Frame number: %d Physical address = %d \n",
		 logicalAddress, pageNumber, offset, frameNumber, physicalAddress);
	}
	munmap(mmapfptr, PAGE_TABLE_SIZE);
	fclose(fptr);
	return 0;
}
