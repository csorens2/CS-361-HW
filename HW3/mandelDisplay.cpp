/*
* Christopher Sorenson
* csorens2
*/
#include "mandelDisplay.h"
#include "structures.h"

#include <iostream>
#include <sys/shm.h>
#include <sys/wait.h>
#include <sys/msg.h>
#include <string.h>
#include <signal.h>

int	shmid, msgqID1, msgqID2;

int main(int argc, char** argv)
{
	
	shmid = atoi(argv[0]);
	msgqID1 = atoi(argv[1]);
	msgqID2 = atoi(argv[2]);
	signal(SIGUSR1,interruptHandler);


	bool gotFilename = false;
	while(true)
	{
		if(gotFilename == false)
		{
			filename_msg message;
			msgrcv(msgqID2, &message,sizeof(struct filename_msg)-sizeof(long),2,0);
			//printf("Filename from main %s \n",message.filename);
			gotFilename = true;
		}
	}
}

void interruptHandler(int sig)
{
	printf("Display caught signal \n");
	if(sig == SIGUSR1){}
		cleanup();
}

void cleanup()
{
	void *shared_memory = shmat(shmid,0,0);
	shmdt(shared_memory);
	printf("Display cleaned up \n");
	exit(0);
}
