# memory-management-simulator
A simple memory management simulator in C that supports paging

The MMU simulates a demand paging system with the following properties:
  - logical address space of 2^16 bytes,
  - physical address space of 2^15 bytes,
  - Size of each page is 256 bytes,
  - TLB size of 16,
  - Page replacement policy is FIFO.

Compile: gcc -o mmu mmu.c
Run: ./mmu
Test: test.py

Collaborated with: Tasnim Noshin
