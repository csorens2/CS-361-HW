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
double 	xMin, xMax, yMin, yMax;
int 	nRows, nCols, maxIter;

int main(int argc, char** argv) 
{
	shmid = atoi(argv[0]);
	msgqID1 = atoi(argv[1]);
	signal(SIGUSR1,interruptHandler);
	signal(SIGSEGV,interruptHandler);


	bool gotInfo = false;
	while(true)
	{	
		if(gotInfo == false)
		{
			fread(info,sizeof(double),8,stdin);
			setupValues();
			gotInfo = true;
			calculations();
		}
	}
}

void calculations()
{
	double deltaX = (xMax - xMin)/(nCols - 1);
	double deltaY = (yMax - yMin)/(nRows - 1);

	void *shared_memory = shmat(shmid,0,0); 
	int *writeData;

	/* Testing writes
	for(int i = 0; i < nRows; i++)
	{
		for(int k = 0; k < nCols; k++)
		{
			writeData = ((int*)(shared_memory) + i*nCols + k);
			*writeData = i % 15;
		}
	}*/
	int n = 0, output = 0;
	for(int r = 0; r < nRows; r++)
	{	
		float cy = yMin + r*deltaY;
		for(int c = 0; c < nCols; c++)
		{
			float cx = xMin + (c*deltaX);
			float zx = 0.0; 
			float zy = 0.0;
			for(n = 0; n < maxIter; n++)
			{
				if( (zx*zx) + (zy*zy) >= 4.0)
					break;
				float zx_next = zx*zx - zy*zy + cx;
				float zy_next = (2.0*zx*zy)+cy;
				zx = zx_next;
				zy = zy_next;
			}
			writeData = ((int*)(shared_memory) + r*nCols + c);
			if(n >= maxIter)
				*writeData = -1;
			else
				*writeData = n;
		}
	}
	write(output,info,8*sizeof(double));
	done_msg message;
	message.mtype = 2;
	message.child = 1;
	msgsnd(msgqID1, &message, sizeof(struct done_msg)-sizeof(long),0);
}

void interruptHandler(int sig)
{	
	//printf("Calc caught signal\n");
	if(sig == SIGUSR1)
	{
		//printf("Calc received SIGUSR1. Exiting\n");
		cleanup();
	}

	if(sig == SIGSEGV)
		printf("Seg fault hit. Exiting\n");
	cleanup();
}

void setupValues()
{
	xMin = info[0];
	xMax = info[1];
	yMin = info[2];
	yMax = info[3];
	nRows = (int)info[4];
	nCols = (int)info[5];
	maxIter = (int)info[6];

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
	exit(0);
}

