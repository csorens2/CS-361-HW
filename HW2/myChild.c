#include <stdio.h>
#include <signal.h>
#include <thread>
#include <chrono>
#include <iostream>
#include <stdlib.h>
#include <setjmp.h>
#include <time.h>
#include <ctype.h>
/*
* Christopher Sorenson
* csorens2
*/
int nSig1;
int count = 0;
void signalHandler(int sig)
{
	if(sig == SIGALRM)
	{	
		if(count < nSig1)
		{
			printf("Daddy?\n");
			kill(getppid(),SIGUSR1);
			count++;
		}
		else
		{
			printf("DADDY!\n");
			kill(getppid(),SIGUSR2);
			return;
		}
	}
	if(sig == SIGUSR1)
	{
		printf("Okay Daddy\n");
		return;
	}
}


void myChild(char* username, int nSigString)
{
	nSig1 = nSigString;
	signal(SIGALRM,signalHandler);
	signal(SIGUSR1,signalHandler);
	printf("Child Name:%s nSig1:%d PID:%d PPID: %d \n",
			username,nSig1,getpid(),getppid());
			
	while(true)
	{
		time_t start = time(NULL);
		alarm(5);
		sleep(10);

		//TODO Remove following comment out to get child time slept
		//printf("Time Child Slept: %d \n",time(NULL) - start);

	}
}
