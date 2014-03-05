/*
* Christopher Sorenson
* csorens2
*/
#include "mandelDisplay.h"
#include "structures.h"

#include <iostream>
#include <fstream>
#include <sys/shm.h>
#include <sys/wait.h>
#include <sys/msg.h>
#include <string.h>
#include <signal.h>
using namespace std;

int	shmid, msgqID1, msgqID2;

double 	xMin, xMax, yMin, yMax;
int 	nRows, nCols, maxIter;
char	fileName[20];

int main(int argc, char** argv)
{	
	shmid = atoi(argv[0]);
	msgqID1 = atoi(argv[1]);
	msgqID2 = atoi(argv[2]);
	signal(SIGUSR1,interruptHandler);
	signal(SIGSEGV,interruptHandler);

	bool gotFilename = false;
	while(true)
	{
		if(gotFilename == false)
		{
			filename_msg message;
			msgrcv(msgqID2, &message,sizeof(struct filename_msg)-sizeof(long),2,0);
			setupValues(message);
			gotFilename = true;
			displayPic();
		}
	}
}

void displayPic()
{
	
	ofstream myfile;
	myfile.open(fileName,std::ofstream::out | std::ofstream::trunc);
	//myfile << "Testing the write process. \n";
	//myfile.close();
	
	
	char colors[16] = ".-~:+*%08&?$@#X";
	void *data = shmat(shmid,0,0);

	for(int r = 0; r < nRows; r++)
	{
		for(int c = 0; c < nCols; c++)
		{
			int n = *((int*)(data) + r*nCols + c);
			if(n < 0)
				myfile << " ";
			else
				myfile << colors[n%15];
			
		}
		myfile << "\n";
	}
	done_msg message;
	message.mtype = 2;
	message.child = 2;
	msgsnd(msgqID1, &message, sizeof(struct done_msg)-sizeof(long),0);
	myfile.close();
}

void interruptHandler(int sig)
{
	//printf("Display caught signal \n");
	if(sig == SIGUSR1)
	{
		//printf("Display received SIGUSR1. Exiting\n");
		cleanup();
	}

	if(sig == SIGSEGV)
		printf("Hit segfault. Exiting\n");	
	cleanup();
}

void setupValues(filename_msg message)
{
	//fileName = message.filename;
	xMin = message.info[0];
	xMax = message.info[1];
	yMin = message.info[2];
	yMax = message.info[3];
	nRows = (int)message.info[4];
	nCols = (int)message.info[5];
	maxIter = (int)message.info[6];
	strcpy(fileName,message.filename);

	/* For debugging
	printf("xMin = %f \n",xMin);
	printf("xMax = %f \n",xMax);
	printf("yMin = %f \n",yMin);
	printf("yMax = %f \n",yMax);
	printf("nRows = %f \n",nRows);
	printf("nCols = %f \n",nCols);
	printf("maxIter = %f \n",maxIter);*/
}

void cleanup()
{
	void *shared_memory = shmat(shmid,0,0);
	shmdt(shared_memory);
	exit(2);
}
