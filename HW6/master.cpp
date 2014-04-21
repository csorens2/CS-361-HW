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
#include <unistd.h>
#include <math.h>

int 	nBuffers, nWorkers, randSeed, shmID, msgqID, semID;
double 	sleepMin, sleepMax;
bool	lock; //True = -lock    False = -nolock

int main(int argc, char** argv)
{
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

	// Setup Message Queue and semaphore
	msgqID = msgget(IPC_PRIVATE, 0666 | IPC_CREAT | IPC_EXCL);
	semID = -1;

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

	int childrenDone = 0;
	worker_message inbox;
	while(childrenDone != nWorkers)
	{
		msgrcv(msgqID, &inbox, sizeof(struct worker_message) - sizeof(long),0,0);
		if(inbox.mtype == 1)//Received a done message from a child
		{
			childrenDone++;
			printf("Child done \n");
		}
		if(inbox.mtype == 2)
		{
			//printf("Data collision hit. Buffer %d fucked up\n",inbox.changedBuffer);
		}
	}

	// Cleanup shm and msgq 
	void *shared_memory = shmat(shmID,0,0);
	shmdt(shared_memory);
	shmctl(shmID,IPC_RMID,0);
	msgctl(msgqID,IPC_RMID,0);
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
	nBuffers = 17;
	nWorkers = 8;
	sleepMin = 0;
	sleepMax = 5;
	lock = false;
}