/*
* Christopher Sorenson
* csorens2
*/

#include "vmpager.h"
#include "structures.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>

char 	inputDataFile[20];
int 	memoryAccesses = 0, frameTableSize = 256;

int main(int argc, char** argv)
{
	printf("Christopher Sorenson\n");
	printf("csorens2\n");

	/* Setup arguments*/
	if(argc == 1)
	{
		printf("Insufficient arguments. Closing\n");
		exit(0);
	}
	if(argc >= 2)
		strncpy(inputDataFile,argv[1],20);
	if(argc >= 3)
		memoryAccesses = atoi(argv[2]);
	if(argc >= 4)
		frameTableSize = atoi(argv[3]);

	/* Open File */
	int fd = open(inputDataFile, O_RDWR);
	if(fd == -1)
	{
		printf("File not opened. Exiting\n");
		exit(0);
	}

	/* fstat the file*/
	struct stat fileStat;
	if(fstat(fd,&fileStat) < 0)
	{
		printf("Fstat failed. Exiting\n");
		exit(0);
	}

	/* mmap the file */
	int fileSize = fileStat.st_size;
	MemoryAccess *memoryTable;
	memoryTable = (MemoryAccess*)mmap(0, fileSize, PROT_READ, MAP_SHARED, fd, 0);

	/* Check if we want to read the whole file */
	if(memoryAccesses == 0)
		memoryAccesses = (int)(fileSize / sizeof(MemoryAccess));


	/* Print out parameters */
	printf("Data file: %s\n", inputDataFile);
	printf("Number of Memory Accesses: %d\n",memoryAccesses);
	printf("Frametable Size: %d\n",frameTableSize);

	/*
	* Our first run through will be with the FIFO algorithm
	*/

	/* Setup Page Table */
	PageTableEntry pageTable[256][256];
	for(int i = 0; i < 256; i++)
	{
		for(int j = 0; j < 256; j++)
		{
			pageTable[i][j].frame = -1;
			pageTable[i][j].pageHits = 0;
			pageTable[i][j].pageMisses = 0;
		}
	}

	/* Setup Frame Table */
	FrameTableEntry frameTable[frameTableSize];
	for(int i = 0; i < frameTableSize; i++)
		frameTable[i].vacant = true;

	/*Begin Algorithm for FIFO*/
	int pageHit = 0;
	int pageMiss = 0;
	int currentFrame = 0;
	for(int i = 0; i < memoryAccesses; i++)
	{
		int currentPid = memoryTable[i].pid;
		int currentPage = memoryTable[i].page;
		if(pageTable[currentPid][currentPage].frame != -1)//HIT
		{
			pageHit++;
			pageTable[currentPid][currentPage].pageHits++;
		}
		else//MISS
		{
			pageMiss++;
			pageTable[currentPid][currentPage].pageMisses++;
			if(frameTable[currentFrame].vacant == true)//Vacant Frame
			{
				frameTable[currentFrame].pid = currentPid;
				frameTable[currentFrame].page = currentPage;
				frameTable[currentFrame].vacant = false;

				pageTable[currentPid][currentPage].frame = currentFrame;
			}
			else//Frame is already taken up
			{
				//Clear the frame from the page table
				int framePid = frameTable[currentFrame].pid;
				int framePage = frameTable[currentFrame].page;
				pageTable[framePid][framePage].frame = -1;

				frameTable[currentFrame].pid = currentPid;
				frameTable[currentFrame].page = currentPage;
				pageTable[currentPid][currentPage].frame = currentFrame;
			}
			currentFrame = (currentFrame + 1)%frameTableSize;
		}
	}
	printf("\nFIFO statistics\n");
	printf("Num of misses: %d\n", pageMiss);
	printf("Num Hits: %d\n", pageHit);
	printf("Num mem accesses: %d \n",memoryAccesses);


	/*
	* Now we reset the values to do the infinite memory calculations
	*/

	/* Reseting the pagetable. We dont need to reset frametable since it isn't used in infinite memory*/
	for(int i = 0; i < 256; i++)
	{
		for(int j = 0; j < 256; j++)
		{
			pageTable[i][j].frame = -1;
			pageTable[i][j].pageHits = 0;
			pageTable[i][j].pageMisses = 0;
		}
	}

	/* Starting the algorithm for infinite memory */
	pageHit = 0;
	pageMiss = 0;
	for(int i = 0; i < memoryAccesses; i++)
	{
		int currentPid = memoryTable[i].pid;
		int currentPage = memoryTable[i].page;
		if(pageTable[currentPid][currentPage].frame != -1)//HIT
		{
			pageHit++;
			pageTable[currentPid][currentPage].pageHits++;
		}
		else//MISS
		{
			pageMiss++;
			pageTable[currentPid][currentPage].pageMisses++;
			pageTable[currentPid][currentPage].frame = 1;
		}
	}

	printf("\nInfinite Memory statistics\n");
	printf("Num of misses: %d\n", pageMiss);
	printf("Num Hits: %d\n", pageHit);
	printf("Num mem accesses: %d \n",memoryAccesses);

}
