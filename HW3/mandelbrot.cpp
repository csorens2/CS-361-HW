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
	//signal(SIGCHLD,childSignalHandler);

	setupSharedMemory();

	setupQueues();

	forkProcesses();

	waitpid(calcPid,NULL,0);
	waitpid(displayPid,NULL,0);
	cleanup();
}

void forkProcesses()
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
		//TODO Renable pipes after done testing
		//dup2(calcPipe[0],0);
		//dup2(childPipe[1],1);
		execl("./mandelCalc", shmID, msgqID1, (char *) 0);
		exit(0);
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
		exit(0);
	}
	close(calcPipe[0]);
	close(childPipe[0]);
	close(childPipe[1]);
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

	pirate_msgbuf guy;
	guy.mtype = 2;
	strncpy(guy.name, "Guybrush Threepwood",30);
	//guy.name = "Guybrush Threepwood";

	msgsnd(atoi(msgqID1), &guy, sizeof(struct pirate_msgbuf)-sizeof(long),0);
}

void setupSharedMemory()
{
	int shmid = shmget(IPC_PRIVATE,1000,0666 | IPC_CREAT | IPC_EXCL);
	char* buffer = new char[20];
	sprintf(buffer,"%d",shmid);
	shmID = buffer;
}

void childSignalHandler(int sig)
{
	waitpid(displayPid,NULL,0);
	waitpid(calcPid,NULL,0);
}

void cleanup()
{
	void *shared_memory = shmat(atoi(shmID), (void*)0,0);
	shmdt(shared_memory);
	shmctl(atoi(shmID),IPC_RMID,0);
	msgctl(atoi(msgqID1),IPC_RMID,0);
	msgctl(atoi(msgqID2),IPC_RMID,0);
}
