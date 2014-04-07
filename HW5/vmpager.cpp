/*
* Christopher Sorenson
* csorens2
*/

#include "vmpager.h"
#include "structures.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char 	inputDataFile[20];
int 	memoryAccesses = 0, frameTableSize = 256;

int main(int argc, char** argv)
{
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


}
