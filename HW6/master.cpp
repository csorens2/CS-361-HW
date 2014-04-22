/*
* Christopher Sorenson
* csorens2
*/

#include "master.h"
#include "message.h"
using namespace std;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <sys/sem.h>
#include <unistd.h>
#include <math.h>





int 	nBuffers, nWorkers, randSeed, shmID, msgqID, semID;
double 	sleepMin, sleepMax;
bool	lock; //True = -lock    False = -nolock

int main(int argc, char** argv)
{
	printf("Christopher Sorenson\ncsorens2\n");
	//First we get the arguments
	if(argc < 5)
	{
		printf("Insufficient arguments. Exiting\n");
		exit(0);
	}
	nBuffers = atoi(argv[1]);
	nWorkers = atoi(argv[2]);
	sleepMin = atof(argv[3]);
	sleepMax = atof(argv[4]);
	randSeed = time(NULL);
	lock = false;
	if(argc > 5)
		randSeed = atoi(argv[5]);
	if(argc > 6)
		if(!strcmp((argv[6]),"-lock"))
			lock = true;

	debugValues(); //REMOVE WHEN FINISHED DEBUGGING

	printf("Running simulation for %d children accessing %d buffers, ",nWorkers,nBuffers);
	if(lock)
		printf("with locking\n\n");
	else
		printf("without locking\n\n");

	// Setup and sort the array
	double workers[nWorkers];
	srand(randSeed);
	for(int i = 0; i < nWorkers; i++)
	{
		workers[i] = (sleepMax - sleepMin)
					 	* ((double)rand() / (double)RAND_MAX)
					 		+ sleepMin;
	}
	qsort(workers, nWorkers, sizeof(double),compareDouble);

	// Setup Message Queue
	msgqID = msgget(IPC_PRIVATE, 0666 | IPC_CREAT | IPC_EXCL);

	// Setup semaphores
	if(lock == false)// No semaphores
		semID = -1;
	else// Using semaphores
	{
		semID = semget(IPC_PRIVATE, nBuffers, 0666 | IPC_CREAT);
		union semun arg;
		arg.val = 1;
		for(int i = 0; i < nBuffers; i++)			
			semctl(semID,i,SETVAL,arg);
	}

	// Setup and zero shared memory array
	shmID = shmget(IPC_PRIVATE, sizeof(int)*(nBuffers+5), 0666 | IPC_CREAT | IPC_EXCL);
	for(int i = 0; i < nBuffers; i++)
		writeToMemory(i,0);

	// Create the children
	for(int i = 0; i < nWorkers; i++)
	{
		if(fork() == 0)// Created Worker
		{
			char 	arg1[10], arg2[10], arg3[10], arg4[10],
					arg5[10], arg6[10];

			sprintf(arg1,"%d",i+1); sprintf(arg2,"%d",nBuffers);
			sprintf(arg3,"%f",workers[i]); sprintf(arg4,"%d",msgqID);
			sprintf(arg5,"%d",shmID); sprintf(arg6,"%d",semID);

			execl("./worker", "", arg1,arg2,arg3,arg4,arg5,arg6, NULL);
		}
	}

	// Wait for messages from workers till they're all done
	int childrenDone = 0;
	int readErrors = 0;
	worker_message inbox;
	while(childrenDone != nWorkers)
	{
		msgrcv(msgqID, &inbox, sizeof(struct worker_message) - sizeof(long),0,0);
		if(inbox.mtype == 1)//Received a done message
			childrenDone++;
		if(inbox.mtype == 2) //Received a read error message
		{
			readErrors++;
			int badBit = log(inbox.finalBufferValue-inbox.initialBufferValue) / log(2);
			printf("Child number %d reported change from %d to %d in buffer %d. Bad bits = %d \n",
						inbox.workerID, inbox.initialBufferValue, inbox.finalBufferValue, 
							inbox.changedBuffer, badBit);
		}
	}
	printf("\n");

	//Find the bad buffers
	int correctNum = pow(2,nWorkers) - 1;
	printf("Expected buffer value: %d\n",correctNum);
	int writeErrors = 0;
	for(int i = 0; i < nBuffers; i++)
	{
		if(readFromMemory(i) != correctNum)// Found bad bit
		{
			writeErrors++;
			printf("Error in buffer %d with value %d. Bad bits =",i,readFromMemory(i));
			for(int j = 0; j < nWorkers; j++)// Cycle through bits to find bad ones
			{
				int currentBit = (readFromMemory(i) >> j) & 1;
				if(currentBit != 1)
					printf(" %d",j);
			}
			printf("\n");
		}
	}
	printf("\n%d Read errors and %d write errors encountered\n",readErrors,writeErrors);

	// Cleanup shm and msgq 
	void *shared_memory = shmat(shmID,0,0);
	shmdt(shared_memory);
	shmctl(shmID,IPC_RMID,0);
	msgctl(msgqID,IPC_RMID,0);
	semctl(semID, IPC_RMID,0);
}

int compareDouble(const void *x, const void *y)
{
	double xx = *(double*)x;
	double yy = *(double*)y;
	if(xx > yy) 
		return -1;
	if(xx < yy) 
		return 1;
	return 0;
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

void debugValues()
{
	nBuffers = 13;
	nWorkers = 6;
	sleepMin = 0;
	sleepMax = .5;
	lock = true;
}