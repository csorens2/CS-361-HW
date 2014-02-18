#include <stdio.h>
#include <signal.h>
#include <thread>
#include <chrono>
#include <iostream>
#include <stdlib.h>
#include <setjmp.h>
#include <time.h>
#include <ctype.h>
#include "myChild.c"
#include <sys/wait.h>
/*
* Christopher Sorenson
* csorens2
*/


int increment;
sigjmp_buf jmpbuff;
int offset = 0;
int childpid = -1;

void childSignalHandler(int sig)
{
	if(sig == SIGUSR1)
	{
		printf("Not right now, Daddy's busy counting internet cookies\n");
		kill(childpid,SIGUSR1);
	}
	if(sig == SIGUSR2)
	{
		printf("Enough! Go back to bed or you're gettin an ass whuppin\n");
		printf("Now, where was I.....\n");
		kill(childpid, SIGKILL);
		_longjmp(jmpbuff,0);
	}
	if(sig == SIGCHLD)
	{
		waitpid(childpid,NULL,0);
		childpid = -1;
	}
}

void keyboardInterrupHandler(int sig)
{
	printf("\nCaught sig %d. Please choose an option \n",sig);
	int input = 0;

startLoop:
	while(true)
	{
		printf("1: Quit Program \n");
		printf("2: Resume with current count increment \n");
		printf("3: Change current count increment and continue \n");
		printf("4: Reset counter \n");
		printf("5: Launch Child Process \n");
		std::cin >> input;
		if(input == 1)
		{
			if(childpid != -1)
			{
				kill(childpid, SIGKILL);
				waitpid(childpid,NULL,0);
			}
			std::exit(0);
		}
		if(input == 2)
			return;
		if(input == 3)
		{
			printf("New Increment Amount?\n");
			std::cin >> increment;
			return;
		}
		if(input == 4)
			_longjmp(jmpbuff,0);
		if(input == 5)
		{	
			if(childpid != -1)
			{
				printf("Child already created. Choose another option\n");
				goto startLoop;
			}
			int nSig1;
			printf("How many times should the child ask before getting yelled at?\n");
			std::cin >> nSig1;
			if(nSig1 < 0)
			{
				printf("Bad amount. Resetting to top menu\n");
				goto startLoop;
			}
			else
			{
				//Start fork
				childpid = fork();
				if(childpid >= 0)
				{
					if(childpid == 0) //child process
					{
						myChild("csorens2",nSig1);
					}
					else //Parent Process
					{
						return;
					}
				}
				else
				{
					printf("ERROR: Fork unexpectdly failed. Exiting\n");
					std::exit(0);	
				}
			}
		}
		if(input > 5 || input < 1)
			printf("Bad input\n");
	}


}

void faultHandler(int sig)
{
	if(sig == SIGFPE)
	{
		printf("Inf\n");
		offset++;
	}
	else if(sig == SIGSEGV)
	{
		printf("Seg-fault has occured\n");
		_longjmp(jmpbuff,0);
	}
	else
	{
		printf("Fault Handler Signal: %d. Exiting \n",sig);
		std::exit(0);
	}

}

int main(int argc, char** argv)
{
	//Beginning Print out
	printf("Christopher Sorenson\n");
	printf("Csorens2\n\n");

	//Argument Checker
	if(argc < 2)
	{
		printf("Insufficient Arguments. Exiting \n");
		return -1;
	}
	int nSleep = atoi(argv[1]);
	if(nSleep < 1)
	{
		printf("Bad sleep amount. Exiting \n");
		return -1;
	}
	short numbers[6];
	char words[6], *name = "CS 361";
	for(int i = 0; i < 6; i++)
	{
		numbers[i] = 100+i;
		words[i] = name[i];
	}

	//Setup signal handling
	signal(SIGINT,keyboardInterrupHandler);
	signal(SIGFPE,faultHandler);
	signal(SIGSEGV,faultHandler);
	signal(SIGUSR1,childSignalHandler);
	signal(SIGUSR2,childSignalHandler);
	signal(SIGCHLD,childSignalHandler);
	
	//Setup jump and start loop
	sigsetjmp(jmpbuff,1);
	int counter = 0;
	increment = 1;
	printf("Starting Count \n");
	while(true)
	{
		counter += increment;
		printf("words[%d] = 0x%x = %d",counter,words[counter],words[counter]);
		if(isprint(words[counter]))
			printf(" = %c", words[counter]);
		offset = 0;
		printf("1.0/ %d = %f \n",(words[counter] + offset), 1.0/(words[counter] + offset));

		time_t start = time(NULL);
		sleep(nSleep);

		//TODO Remove following comment to get time between count
		//printf("Time Slept: %d \n",time(NULL) - start);
	}
}

