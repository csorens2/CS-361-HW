/*
* Christopher Sorenson
* csorens2
*/
#include "mandelbrot.h"
#include "mandelCalc.h"
#include "mandelDisplay.h"

#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <thread>
#include <signal.h>
#include <iostream>
#include <stdarg.h>
#include <unistd.h>
#include <string.h>

// 0 is read end, 1 is write end for pipes
// STDIN = 0 STDOUT = 1

int 	calcPid = -1, displayPid = -1;
int 	calcPipe[2], childPipe[2];
//char 	readbuffer[80];

int main(int argc, char** argv)
{
	//printf("Chris Sorenson \ncsorens2 \n");
	if(pipe(calcPipe) || pipe(childPipe))
	{
		printf("ERROR: Pipe failed. Exiting");
		exit(1);
	}
	signal(SIGCHLD,childSignalHandler);

	forkProcesses();
	write(calcPipe[1], "Testing calcPipe", (strlen("Testing calcPipe")+1));

	waitpid(calcPid,NULL,0);
	waitpid(displayPid,NULL,0);
}

void forkProcesses()
{
	const char* shmID = "test1";
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

		char readbuffer[100];
		read(calcPipe[0],readbuffer,sizeof(readbuffer));
		printf("Received string %s\n",readbuffer);
		write(childPipe[1], "Testing childPipe", (strlen("Testing childPipe")+1));

		dup2(calcPipe[0],0);
		dup2(childPipe[1],1);

		const char* msgqID = "test2";
		execl("./mandelCalc",shmID, msgqID, (char *) 0);
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

		char readbuffer2[100];
		read(childPipe[0],readbuffer2,sizeof(readbuffer2));
		printf("Received string %s\n",readbuffer2);

		dup2(childPipe[0],0);

		const char* msgqID1 = "test3";
		const char* msgqID2 = "test4";
		execl("./mandelDisplay", shmID, msgqID1, msgqID2,(char *) 0);
	}
	close(calcPipe[0]);
	close(childPipe[0]);
	close(childPipe[1]);
}

void setupQueues()
{
	
}

void childSignalHandler(int sig)
{
	waitpid(displayPid,NULL,0);
	waitpid(calcPid,NULL,0);
}
