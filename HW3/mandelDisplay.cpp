/*
* Christopher Sorenson
* csorens2
*/
#include "mandelDisplay.h"

#include <iostream>
#include <sys/shm.h>
#include <sys/wait.h>
#include <sys/msg.h>

int	shmid;

int main(int argc, char** argv)
{
	shmid = atoi(argv[0]);

	cleanupMemory();
}
/*Example of getting data from shared memory
	void *shared_memory = shmat(shmid, 0,0);
	int* test = (int*)(shared_memory);
	printf("Value from shared memory %d \n",(*test));*/

/* Example of reading values from stdin (Calc)
	char buffer[100];
	fread(buffer, sizeof(char), 20, stdin);*/
void cleanupMemory()
{
	void *shared_memory = shmat(shmid, (void*)0,0);
	shmdt(shared_memory);
}
