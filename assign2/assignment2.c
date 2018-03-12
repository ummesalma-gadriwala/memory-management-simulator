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

#define TLB_SIZE 16
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
typedef struct {
	int pageNumber;
	int frameNumber;
} TLBentry;

/////////////////////////////////////////////
TLBentry *TLBarray[TLB_SIZE];
////////////////////////////////////////////

// return frameNumber of page, -1 if page does not exist in TLB 
int search_TLB(int page) {
	int i;
	for(i = 0; i < TLB_SIZE; i++) {
		if (TLBarray[i]->pageNumber == page) {
			return TLBarray[i]->frameNumber;
		}
	}
	return -1;
}

// return new position of the oldest entry in TLB
//int TLB_Add(TLBentry *newEntry, int oldestEntryPosition) {
//	TLBarray[oldestEntryPosition%TLB_SIZE] = newEntry;
//	oldestEntryPosition++;
//	return oldestEntryPosition;
//}

// return new position of the oldest entry in TLB
// update page and frame numbers at position
int TLB_Add(int page, int frame, int oldestEntryPosition) {
	TLBarray[oldestEntryPosition%TLB_SIZE]->pageNumber = page;
	TLBarray[oldestEntryPosition%TLB_SIZE]->frameNumber = frame;
	oldestEntryPosition++;
	return oldestEntryPosition;
}

// replacedPage and newPage have same location/frame in physical memory
// return 0 if updated, -1 if not
int TLB_Update(int replacedPage, int newPage) {
	int i;
	for (i = 0; i < TLB_SIZE; i++) {
		if (TLBarray[i]->pageNumber == replacedPage) {
			TLBarray[i]->pageNumber = newPage;
			return 0;
		}
	}
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
	int totalAddr = 0;
	int frameNumber;
	int i;
	int page_table[PAGES];
	char *physical_memory[FRAMES];
////////////////////////////////////////////	
	for(i = 0; i < TLB_SIZE; i++) {
		TLBentry *t = (TLBentry *) malloc (sizeof(TLBentry));
		t->pageNumber = -1;
		t->frameNumber = -1;
		TLBarray[i] = t;
	}
////////////////////////////////////////////
    for(i = 0; i < FRAMES; i++) {
        physical_memory[i] = (char *) malloc(PAGE_SIZE);
    }
	for (i = 0; i < PAGES; i++) {
		page_table[i] = -1;
	}
	
	int nextFrame = 0;
	int nextTLBFrame = 0;
	/**************HANDLING PAGE FAULTS**************/
		// open file in read-only mode
	int fBS = open("BACKING_STORE.bin", O_RDONLY);
    if(fBS < 0) return 1; // if file is not correctly opened
    	// map BACKING_STORE to a memory region
    signed char *mmapfptr = mmap(0, BS_SIZE, PROT_READ, MAP_PRIVATE, fBS, 0);
    close(fBS);
	
	
	while (fgets(buff, BUFFER_SIZE, fptr) != NULL) {
		totalAddr++;
		// buff is a pointer to each line/address from the file
		logicalAddress = atoi(buff);
		pageNumber = logicalAddress >> OFFSET_BITS;
		offset = logicalAddress & OFFSET_MASK;		
		// LOOK UP TLB
		////////////////////////////////////////////
		frameNumber = search_TLB(pageNumber);
		if (frameNumber != -1) { // found in TLB
			hitCount++;
		} else { // not found in TLB
		////////////////////////////////////////////
			// LOOK UP IN PAGE TABLE
				// found in page table
			frameNumber = page_table[pageNumber];
				// add to TLB
			if (frameNumber != -1) {
				nextTLBFrame = TLB_Add(pageNumber, frameNumber, nextTLBFrame);
				// when page fault occurs
			} else if (frameNumber == -1) {
				faultCount++;
				// get the page at the pageNumber from the mapped data
				// put it in the next available frame
				// change the page table entry
				// update page table
				int oldPage;
				memcpy(physical_memory[nextFrame%FRAMES], mmapfptr + (pageNumber*256), 256);
				for (i = 0; i < PAGES; i++) {
					if (page_table[i] == nextFrame%FRAMES) {
						page_table[i] = -1;
						oldPage = i;
					}
				}
				page_table[pageNumber] = nextFrame%FRAMES;
				frameNumber = page_table[pageNumber];
				nextFrame++;
				int success = TLB_Update(oldPage, pageNumber);
				if (success == -1)
					nextTLBFrame = TLB_Add(pageNumber, frameNumber, nextTLBFrame);
			}
		}
		physicalAddress = (frameNumber << OFFSET_BITS) | offset;
		value = physical_memory[frameNumber][offset];
		printf("Virtual address: %d Page#:%d Offset:%d Physical address = %d Value=%d\n", logicalAddress, pageNumber, offset, physicalAddress, value);
	}
	munmap(mmapfptr, BS_SIZE);
	fclose(fptr);
	printf("Total addresses: %d\n", totalAddr);
	printf("Page_faults: %d\n",faultCount);
	printf("TLB Hits: %d\n",hitCount);
	//////////////////////////////////////////////
	// deallocate memory on the heap
	for(i = 0; i < FRAMES; i++) {
		free(physical_memory[i]);
	}
	for(i = 0; i < TLB_SIZE; i++) {
		free(TLBarray[i]);
	}
	/////////////////////////////////////////////////////
	return 0;
}
