/*
* Christopher Sorenson
* csorens2
*/

#include "worker.h"
#include "message.h"
using namespace std;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <unistd.h>
#include <math.h>

int		workerID, nBuffers, msgqID, shmID, semID;
double	sleepTime;

int main(int argc, char** argv)
{
	//First get the arguments
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

	//Begin the algorithm
	int currentPos = workerID;
	int a, b, c, newA, newB, newC;
	for(int i = 0; i < nBuffers; i++)
	{
		//First Read
		b = readFromMemory(currentPos);
		usleep(sleepTime * 1000000);
		newB = readFromMemory(currentPos);
		if(b != newB)
		{
			worker_message errorMessage;
			errorMessage.mtype = 2;
			errorMessage.workerID = workerID;
			errorMessage.changedBuffer = currentPos;
			errorMessage.initialBufferValue = b;
			errorMessage.finalBufferValue = newB;
			msgsnd(msgqID, &errorMessage, sizeof(struct worker_message) - sizeof(long),0);
		}
		currentPos = (currentPos + workerID) % nBuffers;

		//Second Read
		c = readFromMemory(currentPos);
		usleep(sleepTime * 1000000);
		newC = readFromMemory(currentPos);
		if(c != newC)
		{
			worker_message errorMessage;
			errorMessage.mtype = 2;
			errorMessage.workerID = workerID;
			errorMessage.changedBuffer = currentPos;
			errorMessage.initialBufferValue = c;
			errorMessage.finalBufferValue = newC;
			msgsnd(msgqID, &errorMessage, sizeof(struct worker_message) - sizeof(long),0);
		}
		currentPos = (currentPos + workerID) % nBuffers;
		
		//Write
		a = readFromMemory(currentPos);
		usleep(sleepTime * 1000000);
		writeToMemory(currentPos, a + (1 << (workerID - 1)));
		currentPos = (currentPos + workerID) % nBuffers;
	}

	worker_message done;
	done.mtype = 1;
	msgsnd(msgqID, &done, sizeof(struct worker_message) - sizeof(long),0);

	//Detach shared memory
	void *shared_memory = shmat(shmID,0,0);
	shmdt(shared_memory);
}

void writeToMemory(int pos, int value)
{
	void *shared_memory = shmat(shmID,0,0);
	int* arr = (int*)shared_memory;
	arr[pos] = value;
}

int readFromMemory(int pos)
{
	void *shared_memory = shmat(shmID,0,0);
	int* arr = (int*)shared_memory;
	return arr[pos];
}