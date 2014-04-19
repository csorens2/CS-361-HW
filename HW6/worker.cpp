/*
* Christopher Sorenson
* csorens2
*/

#include "worker.h"
#include "message.h"
using namespace std;

#include <stdio.h>
#include <stdlib.h>

int		workerID, nBuffers, msgID, shmID, semID;
double	sleepTime;

int main(int argc, char** argv)
{
	if(argc < 6)
	{
		printf("Insufficient Arguments. Exiting\n");
		exit(0);
	}
	workerID = atoi(argv[1]);
	nBuffers = atoi(argv[2]);
	sleepTime = atof(argv[3]);
	msgID = atoi(argv[4]);
	shmID = atoi(argv[5]);
	semID = -1;
	if(argc > 6)
		semID = atoi(argv[6]);
}