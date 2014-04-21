/*
* Christopher Sorenson
* csorens2
*/

#include "worker.h"
#include "message.h"
using namespace std;

#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/msg.h>

int		workerID, nBuffers, msgqID, shmID, semID;
double	sleepTime;

int main(int argc, char** argv)
{
	/* First get the arguments */
	if(argc < 6)
	{
		printf("Insufficient Arguments. Exiting\n");
		exit(0);
	}
	workerID = atoi(argv[1]);
	nBuffers = atoi(argv[2]);
	sleepTime = atof(argv[3]);
	msgqID = atoi(argv[4]);
	shmID = atoi(argv[5]);
	semID = -1;
	if(argc > 6)
		semID = atoi(argv[6]);
/*	printf("Worker %d nBuffer:%d SleepTime:%f msgqID:%d shmID:%d semID:%d\n",
			workerID, nBuffers, sleepTime, msgqID, shmID, semID);*/

}

void writeToMemory(int pos, int value)
{
	void *shared_memory = shmat(shmID,0,0);
	int *intPointer = ((int*)(shared_memory) + pos);
	*intPointer = value;
}

int readFromMemory(int pos)
{
	void *shared_memory = shmat(shmID,0,0);
	int *intPointer = ((int*)(shared_memory) + pos);
	return *intPointer;
}