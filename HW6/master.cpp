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

int 	nBuffers, nWorkers, randSeed;
double 	sleepMin, sleepMax;
bool	lock; //True = -lock    False = -nolock

int main(int argc, char** argv)
{
	/*First we get the arguments*/
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

	/* Setup and sort the array */
	double workers[nWorkers];
	srand(randSeed);
	for(int i = 0; i < nWorkers; i++)
	{
		workers[i] = (sleepMax - sleepMin)
					 	* ((double)rand() / (double)RAND_MAX)
					 		+ sleepMin;
	}
	qsort(workers, nWorkers, sizeof(double),compareDouble);

	/* Setup shared memory and message queue */
	int shmid = shmget(IPC_PRIVATE, 100000, 0666 | IPC_CREAT | IPC_EXCL);
	int msgqID = msgget(IPC_PRIVATE, 0666 | IPC_CREAT | IPC_EXCL);

}

int compareDouble(const void *x, const void *y)
{
	double xx = *(double*)x;
	double yy = *(double*)y;
	if(xx < yy) 
		return -1;
	if(xx > yy) 
		return 1;
	return 0;
}