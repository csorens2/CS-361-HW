/*
* Christopher Sorenson
* csorens2
*/
#include "mandelCalc.h"

#include <iostream>
#include <sys/shm.h>
#include <sys/wait.h>
#include <sys/msg.h>

int shmid;

int main(int argc, char** argv) 
{
	shmid = atoi(argv[0]);

	cleanupMemory();
}
/* Example of sending memory to display
	void *shared_memory = shmat(shmid,0,0);
	int* test = (int*)(shared_memory);
	*test = 8675309;*/
void cleanupMemory()
{
	void *shared_memory = shmat(shmid, (void*)0,0);
	shmdt(shared_memory);
}

