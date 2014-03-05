/*
* Christopher Sorenson
* csorens2
*/
#include "mandelbrot.h"
#include "structures.h"

#include <iostream>
#include <sys/shm.h>
#include <sys/wait.h>
#include <sys/msg.h>
#include <string.h>
#include <signal.h>


// 0 is read end, 1 is write end for pipes
// STDIN = 0 STDOUT = 1

int 		calcPid = -1, displayPid = -1;
int 		calcPipe[2], childPipe[2];
char		fileName[20];
double 		xMin, xMax, yMin, yMax, nRows, nCols, maxIter;
int 		numPictures;
const char* shmID;
const char* msgqID1;
const char* msgqID2;

int main(int argc, char** argv)
{
	printf("Chris Sorenson \ncsorens2 \n");
	numPictures = 0;

start:
	setupSharedMemory();

	setupQueues();

	forkProcesses();

	signal(SIGCHLD,childSignalHandler);
	signal(SIGINT,keyboardInterruptHandler);

	readPipeInputs();

	bool displayDone = false;
	bool calcDone = false;
	while(true)
	{
		done_msg message;
		msgrcv(atoi(msgqID1), &message, sizeof(struct done_msg)-sizeof(long),2,0);
		if(message.child == 1)
		{
			//printf("Confirmed Calc being done \n");
			sendMessage();
			calcDone = true;
		}
		if(message.child == 2)
		{
			//printf("Received display being done \n");
			displayDone = true;
		}
		if(displayDone && calcDone)
		{
			kill(calcPid,SIGUSR1);
			waitpid(calcPid,NULL,0);
			kill(displayPid,SIGUSR1);
			waitpid(displayPid,NULL,0);
			cleanup();
			printf("Done with current picture. Starting Over\n");
			numPictures++;
			goto start;
		}
	}

}

void forkProcesses() //Also sets up pipes
{
	if(pipe(calcPipe) || pipe(childPipe))
	{
		printf("ERROR: Pipe failed. Exiting");
		exit(1);
	}
	calcPid = fork();
	if(calcPid == -1)
	{
		printf("ERROR: Calc Fork failed. Exiting");
		exit(1);
	}
	if(calcPid == 0) //Launch Calc Process
	{
		close(calcPipe[1]);
		close(childPipe[0]);
		dup2(calcPipe[0],0);
		//dup2(childPipe[1],1);
		execl("./mandelCalc", shmID, msgqID1, (char *) 0);
		printf("Exec mandelcalc failed \n");
	}
	
	displayPid = fork();
	if(displayPid == -1)
	{
		printf("ERROR: Display Fork Failed. Exiting");
		exit(1);
	}
	if(displayPid == 0)//Launch Display Process
	{
		close(calcPipe[1]);
		close(calcPipe[0]);
		close(childPipe[1]);
		dup2(childPipe[0],0);
		execl("./mandelDisplay", shmID, msgqID1, msgqID2, (char *) 0);
		printf("Exec mandeldisplay failed");
	}
	close(calcPipe[0]);
	close(childPipe[0]);
	close(childPipe[1]);
	printf("Waiting for children to setup \n");
	sleep(2);
}

void setupQueues()
{
	//Remove queue "ipcrm -q X"

	char* buffer = new char[20];
	int msgqID = msgget(IPC_PRIVATE, 0666 | IPC_CREAT | IPC_EXCL);
	sprintf(buffer,"%d",msgqID);
	msgqID1 = buffer;

	buffer = new char[20];
	msgqID = msgget(IPC_PRIVATE, 0666 | IPC_CREAT | IPC_EXCL);
	sprintf(buffer,"%d",msgqID);
	msgqID2 = buffer;
}

void setupSharedMemory()
{
	int shmid = shmget(IPC_PRIVATE,100000,0666 | IPC_CREAT | IPC_EXCL);
	char* buffer = new char[20];
	sprintf(buffer,"%d",shmid);
	shmID = buffer;
}

void sendMessage()
{
	filename_msg message;	
	message.mtype = 2;
	message.info[0] = xMin;
	message.info[1] = xMax;
	message.info[2] = yMin;
	message.info[3] = yMax;
	message.info[4] = nRows;
	message.info[5] = nCols;
	message.info[6] = maxIter;
	strncpy(message.filename,fileName,20);
	msgsnd(atoi(msgqID2), &message, sizeof(struct filename_msg)-sizeof(long),0);
}

void readPipeInputs()
{
	char buffer[20];
	double r[7] = {};		

	printf("Filename: ");
	std::cin >> buffer;
	strncpy(fileName,buffer,20);
	sleep(2);

	printf("xMin: ");
	std::cin >> buffer;
	r[0] = atof(buffer);
					
	printf("xMax: ");
	std::cin >> buffer;
	r[1] = atof(buffer);

	printf("yMin: ");
	std::cin >> buffer;
	r[2] = atof(buffer);

	printf("yMax: ");
	std::cin >> buffer;
	r[3] = atof(buffer);

	printf("nRows: ");
	std::cin >> buffer;
	r[4] = atof(buffer);

	printf("nCols: ");
	std::cin >> buffer;
	r[5] = atof(buffer);

	printf("maxIters: ");
	std::cin >> buffer;
	r[6] = atof(buffer);

	/* Used for making calc
	r[0] = -2.0;
	r[1] = 2.0;
	r[2] = -1.5;
	r[3] = 1.5;
	r[4] = 50.0;
	r[5] = 80.0;
	r[6] = 100.0;*/

	xMin = r[0];
	xMax = r[1];
	yMin = r[2];
	yMax = r[3];
	nRows = r[4];
	nCols = r[5];
	maxIter = r[6];


	write(calcPipe[1],r,8*sizeof(double));	
}


void childSignalHandler(int sig)
{
	//printf("Child exited\n");
	//TODO
}

void keyboardInterruptHandler(int sig)
{
	//Cleanup child processes when kill command comes
	printf("\nKeyboard Interrupt caught. Exiting \n");
	printf("Number of Pictures: %d \n",numPictures);
	cleanup();
	kill(calcPid,SIGUSR1);
	waitpid(calcPid,NULL,0);
	kill(displayPid,SIGUSR1);
	waitpid(displayPid,NULL,0);
	exit(0);
}

void cleanup()
{
	void *shared_memory = shmat(atoi(shmID), 0,0);
	shmdt(shared_memory);
	shmctl(atoi(shmID),IPC_RMID,0);
	msgctl(atoi(msgqID1),IPC_RMID,0);
	msgctl(atoi(msgqID2),IPC_RMID,0);
	close(calcPipe[1]);
}
