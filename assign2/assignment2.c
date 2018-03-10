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
#define FRAMES 128
#define OFFSET_BITS 8
#define PAGE_SIZE 256
#define BS_SIZE 65536
/**
Page size = Frame size = 256 bytes = 2048 bits = 2^11
Number of bits required to represent offset = 11
Number of bits required to represent page number = 5
Number of pages = 2^8 = 256
Size of LAS = 2^16 bytes = 65536 bytes
Size of PAS = 2^15 bytes = 32768 bytes
Number of frames = 128
Number of entries in TLB = 16
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
	signed char value;
	int hitCount = 0; // total number of TLB hits
	int faultCount = 0; // total number of page faults
	unsigned int pageNumber;
	int offset;
	int frameNumber;
	int i;
	int page_table[PAGES];
	char *physical_memory[FRAMES];
    for(i = 0; i < FRAMES; i++) {
        physical_memory[i] = (char *) malloc(PAGE_SIZE);
    }
	for (i = 0; i < PAGES; i++) {
		page_table[i] = -1;
	}
	int nextFrame = 0;
	
	/**************HANDLING PAGE FAULTS**************/
		// open file in read-only mode
	int fBS = open("BACKING_STORE.bin", O_RDONLY);
    if(fBS < 0) return 1; // if file is not correctly opened
    	// map BACKING_STORE to a memory region
    signed char *mmapfptr = mmap(0, BS_SIZE, PROT_READ, MAP_PRIVATE, fBS, 0);
    close(fBS);
	
	
	while (fgets(buff, BUFFER_SIZE, fptr) != NULL) {
		// buff is a pointer to each line/address from the file
		logicalAddress = atoi(buff);
		pageNumber = logicalAddress >> OFFSET_BITS;
		offset = logicalAddress & OFFSET_MASK;		
		// LOOK UP TLB
		// LOOK UP IN PAGE TABLE
		frameNumber = page_table[pageNumber];
		
		// when page fault occurs
		if (frameNumber == -1) {
			faultCount++;
			// get the page at the pageNumber from the mapped data
			// put it in the next available frame
			// change the page table entry
			memcpy(physical_memory[nextFrame % FRAMES], mmapfptr + (pageNumber*256), 256);
			//printf("Page number:%d Frame written: %d\n", pageNumber, nextFrame);
			page_table[pageNumber] = nextFrame%FRAMES;
			frameNumber = page_table[pageNumber];
			nextFrame++;
		}
		physicalAddress = (frameNumber << OFFSET_BITS) | offset;
		value = physical_memory[frameNumber][offset];
		printf("Virtual address: %d (Frame# = %d) Physical address = %d Value=%d\n",
		logicalAddress, frameNumber, physicalAddress, value);
		
	}
	munmap(mmapfptr, BS_SIZE);
	fclose(fptr);
	printf("Page faults: %d\n",faultCount);
	return 0;
}
