/*
* Christopher Sorenson
* csorens2
*/
#include "mandelCalc.h"
#include "structures.h"

#include <iostream>
#include <sys/shm.h>
#include <sys/wait.h>
#include <sys/msg.h>
#include <string.h>
#include <signal.h>

#include <limits.h>

int shmid, msgqID1;

double 	info[7];
double 	xMin, xMax, yMin, yMax, nRows, nCols, maxIter;

int main(int argc, char** argv) 
{
	shmid = atoi(argv[0]);
	msgqID1 = atoi(argv[1]);
	signal(SIGUSR1,interruptHandler);


	bool gotInfo = false;
	while(true)
	{		
		if(gotInfo == false)
		{
			fread(info,sizeof(double),8,stdin);
			//printf("Successfully read values\n");
			setupValues();
			gotInfo = true;
			calculations();
		}
	}
}

void calculations()
{
	// -2 < x < 2
	// -1.5 < y < 2
	// Maxiter = 100;
	// nRows = 20 nCols = 50
	double deltaX = (xMax - xMin)/(nCols - 1);
	double deltaY = (yMax - yMin)/(nRows - 1);

	void *data = shmat(shmid,0,0); //Data will be stored as ints
	int *writeData;
	
	double r, c, n;

	printf("Data address %p \n",data);
	
	for(r = 0; r < nRows; r++)
	{	
		int cy = yMin + r*deltaY;
		for(c = 0; c < nCols; c++)
		{
			int cx = xMin + (c*deltaX);
			int zx = 0.0, zy = 0.0;
			for(n = 0; n < maxIter; n++)
			{
				if( (zx*zx) + (zy*zy) >= 4.0)
					break;
				int zx_next = zx*zx - zy*zy + cx;
				int zy_next = (2.0*zx*zy)+cy;
				zx = zx_next;
				zy = zy_next;
			}
			writeData = ((int*)(data) + (int)(r*nCols) + (int)c);
			if(n >= maxIter)
				*writeData = -1;
			else
				*writeData = n;
		}
	}
	done_msg message;
	message.mtype = 1;
	message.child = 1;
	msgsnd(msgqID1, &message, sizeof(struct done_msg)-sizeof(long),0);
}

void interruptHandler(int sig)
{	
	printf("Calc caught signal\n");
	if(sig == SIGUSR1){}
		cleanup();
}

void setupValues()
{
	xMin = info[0];
	xMax = info[1];
	yMin = info[2];
	yMax = info[3];
	nRows = info[4];
	nCols = info[5];
	maxIter = info[6];

	/* For debugging
	printf("xMin = %f \n",xMin);
	printf("xMax = %f \n",xMax);
	printf("yMin = %f \n",yMin);
	printf("yMax = %f \n",yMax);
	printf("nRows = %d \n",nRows);
	printf("nCols = %d \n",nCols);
	printf("maxIter = %d \n",maxIter);*/
}

void cleanup()
{
	void *shared_memory = shmat(shmid, 0,0);
	shmdt(shared_memory);
	printf("Calc cleaned up \n");
	exit(0);
}

