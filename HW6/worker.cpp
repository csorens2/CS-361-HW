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
#include <sys/sem.h>
#include <unistd.h>
#include <math.h>

int		workerID, nBuffers, msgqID, shmID, semID;
bool	lock;
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
	semID = atoi(argv[6]);
	if(semID == -1)
		lock = false;
	else
		lock = true;

	//Begin the algorithm
	int currentPos = workerID;
	int a, b, c, newA, newB, newC;

	sembuf WAIT, SIGNAL;
	WAIT.sem_op = -1;
	WAIT.sem_flg = SEM_UNDO;

	SIGNAL.sem_op = 1;
	SIGNAL.sem_flg = SEM_UNDO;


	for(int i = 0; i < nBuffers; i++)
	{
		if(lock)
		{
			WAIT.sem_num = currentPos;
			SIGNAL.sem_num = currentPos;
			semop(semID,&WAIT,1);
		}
		//First Read
		b = readFromMemory(currentPos);
		usleep(sleepTime * 1000000);
		newB = readFromMemory(currentPos);
		if(b != newB)
			sendMessage(2,workerID,currentPos,b,newB);
		if(lock)
			semop(semID,&SIGNAL,1);
		currentPos = (currentPos + workerID) % nBuffers;

		if(lock)
		{
			WAIT.sem_num = currentPos;
			SIGNAL.sem_num = currentPos;
			semop(semID,&WAIT,1);
		}
		//Second Read
		c = readFromMemory(currentPos);
		usleep(sleepTime * 1000000);
		newC = readFromMemory(currentPos);
		if(c != newC)
			sendMessage(2,workerID,currentPos,c,newC);
		if(lock)
			semop(semID,&SIGNAL,1);
		currentPos = (currentPos + workerID) % nBuffers;
		
		if(lock)
		{
			WAIT.sem_num = currentPos;
			SIGNAL.sem_num = currentPos;
			semop(semID,&WAIT,1);
		}
		//Write
		a = readFromMemory(currentPos);
		usleep(sleepTime * 1000000);
		writeToMemory(currentPos, a + (1 << (workerID - 1)));
		if(lock)
			semop(semID,&SIGNAL,1);
		currentPos = (currentPos + workerID) % nBuffers;
	}

	//Send done message
	sendMessage(1,0,0,0,0);

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

void sendMessage(int mtype, int workerID, int currentPos, int initial, int final)
{
	//Mtype = 1: Done
	//Mtype = 2: Error
	worker_message message;
	message.mtype = mtype;
	message.workerID = workerID;
	message.changedBuffer = currentPos;
	message.initialBufferValue = initial;
	message.finalBufferValue = final;
	msgsnd(msgqID, &message, sizeof(struct worker_message) - sizeof(long),0);
}