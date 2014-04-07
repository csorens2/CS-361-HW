#ifndef STRUCTURES_H_
#define STRUCTURES_H_

#include <stdint.h>

typedef struct {
	uint8_t pid;
	uint8_t page;
} MemoryAccess;

typedef struct {
	int frame;
	int pageHits;
	int pageMisses;
} PageTableEntry;

typedef struct {
	uint8_t pid;
	uint8_t page;
	bool vacant;
} FrameTableEntry;

#endif