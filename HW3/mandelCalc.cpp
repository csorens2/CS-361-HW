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

int shmid, msgqID1;

int main(int argc, char** argv) 
{
	shmid = atoi(argv[0]);
	msgqID1 = atoi(argv[1]);

	pirate_msgbuf pirate;
	msgrcv(msgqID1, &pirate, sizeof(struct pirate_msgbuf) - sizeof(long),2,0);
	printf("What is your name? \n%s \n",pirate.name);

	cleanup();
}
/* Example of sending memory to display
	void *shared_memory = shmat(shmid,0,0);
	int* test = (int*)(shared_memory);
	*test = 8675309;*/
void cleanup()
{
	void *shared_memory = shmat(shmid, 0,0);
	shmdt(shared_memory);
}

