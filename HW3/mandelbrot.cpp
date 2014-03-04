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
const char* shmID;
const char* msgqID1;
const char* msgqID2;

int main(int argc, char** argv)
{
	//printf("Chris Sorenson \ncsorens2 \n");
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
	int shmid = shmget(IPC_PRIVATE,1000,0666 | IPC_CREAT | IPC_EXCL);
	char* buffer = new char[20];
	sprintf(buffer,"%d",shmid);
	shmID = buffer;
}

void readPipeInputs()
{
	char buffer[20];
	double r[7] = {};		

/*
	printf("Filename: ");
	std::cin >> buffer;
	filename_msg message;	
	message.mtype = 2;
	strncpy(message.filename,buffer,20);
	msgsnd(atoi(msgqID2), &message, sizeof(struct filename_msg)-sizeof(long),0);
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
	r[6] = atof(buffer);*/

	//Used for making calc
	r[0] = -2.0;
	r[1] = -1.5;
	r[2] = 2;
	r[3] = 1.5;
	r[4] = 80.0;
	r[5] = 50.0;
	r[6] = 100.0;

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
	printf("\nKeyboard Interrupt caught \n");
	cleanup();
}

void cleanup()
{
	void *shared_memory = shmat(atoi(shmID), 0,0);
	shmdt(shared_memory);
	shmctl(atoi(shmID),IPC_RMID,0);
	msgctl(atoi(msgqID1),IPC_RMID,0);
	msgctl(atoi(msgqID2),IPC_RMID,0);
	close(calcPipe[1]);
	exit(0);
}
