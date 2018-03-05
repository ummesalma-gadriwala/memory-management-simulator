// Tasnim Noshin
// Umme Salma Gadriwala

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#define BUFFER_SIZE 10

#define OFFSET_MASK 2047
#define PAGES 32
#define OFFSET_BITS 11
#define PAGE_SIZE 2048
/**
Page size = 256 bytes = 2048 bits = 2^11
Number of bits required to represent offset = 11
Number of bits required to represent page number = 5
Number of pages = 2^5
Size of LAS = 2^16 bytes = 25536 bytes
Size of PAS = 2^15 bytes = 32768 bytes
**/
struct TLBentry {
	int pageNumber;
	int frameNumber;
};

/* return frameNumber corresponding to pageNumber */
int search_TLB(int pageNumber) {
	return -1;
}

/* return 0 if success, -1 if error occurs */
int TLB_Add(void) {
	return -1;
}

/* return 0 if success, -1 if error occurs */
int TLB_Update(void) {
	return -1;
}

int main(void) {
	FILE *fptr = fopen("addresses.txt", "r");
	char buff[BUFFER_SIZE];
	unsigned int logicalAddress;
	int physicalAddress;
	int hitCount = 0; // total number of TLB hits
	int faultCount = 0; // total number of page-faults
	unsigned int pageNumber;
	int offset;
	int frameNumber;
	int page_table[PAGES];
	int i;
	for (i = 0; i < PAGES; i++) {
		page_table[i] = -1;
	}
	
	/**************HANDLING PAGE FAULTS**************/
		// open file in read-only mode
	int fBS = open("BACKING_STORE.bin", O_RDONLY);
    if(fBS < 0) return 1; // if file is not correctly opened
    	// map BACKING_STORE to a memory region
    void* mmapData = mmap(NULL, 65536, PROT_READ, MAP_PRIVATE, fBS, 0);
    close(fBS);
	
	
	while (fgets(buff, BUFFER_SIZE, fptr) != NULL) {
		// buff is a pointer to each line/address from the file
		logicalAddress = atoi(buff);
		pageNumber = logicalAddress >> OFFSET_BITS;
		offset = logicalAddress & OFFSET_MASK;		
		// LOOK UP TLB
		// LOOK UP PAGE TABLE
		frameNumber = page_table[pageNumber];
		physicalAddress = (frameNumber << OFFSET_BITS) | offset;
		printf("Virtual address: %d - Page# = %d & Offset = %d. Physical address: %d\n",
		logicalAddress, pageNumber, offset, physicalAddress);
		
		// when page fault occurs
			// get the page at the pageNumber from the mapped data
		memcpy(physicalAddress, mmapData + (pageNumber*256), 256);
	}
	fclose(fptr);
	return 0;
}
