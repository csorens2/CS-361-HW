#include <stdio.h>
#include <signal.h>
#include <thread>
#include <chrono>
#include <iostream>
#include <stdlib.h>
#include <setjmp.h>
#include <time.h>
/*
* Christopher Sorenson
* csorens2
*/


int increment;
sigjmp_buf jmpbuff;
int offset = 0;

void keyboardInterrupHandler(int sig)
{
	printf("\nCaught sig %d. Please choose an option \n",sig);
	int input = 0;
	while(true)
	{
		printf("1: Quit Program \n");
		printf("2: Resume with current count increment \n");
		printf("3: Change current count increment and continue \n");
		printf("4: Reset counter \n");
		std::cin >> input;
		if(input == 1)	
			std::exit(0);	
		else if(input == 2)
			return;
		else if(input == 3)
		{
			printf("New Increment Amount?\n");
			std::cin >> increment;
		}
		else if(input == 4)
			_longjmp(jmpbuff,0);
		else
			printf("Bad input\n");
	}


}

int main(int argc, char** argv)
{
	//Beginning Print out
	printf("Christopher Sorenson\n");
	printf("Csorens2\n");
	//Argument Checker
	if(argc < 1)
	{
		printf("Insufficient Arguments \n");
		return 0;
	}
	int nSleep = atoi(argv[1]);
	if(nSleep < 1)
	{
		printf("Bad sleep amount \n");
		return 0;
	}
	//Setup Interrupt and Jump
	signal(2,keyboardInterrupHandler);
	sigsetjmp(jmpbuff,1);

	short numbers[6];
	char words[6], *name = "CS 361";
	for(int i = 0; i < 6; i++)
	{
		numbers[i] = 100+i;
		words[i] = name[i];
	}

	//Setup and continue loop
	int localCounter = 0;
	increment = 1;
	printf("Starting Count \n");
	while(true)
	{
		printf("Current Counter: %d \n",localCounter);
		localCounter += increment;
	
		time_t start = time(NULL);
		sleep(nSleep);
		printf("Time Slept: %d \n",time(NULL) - start);
	}
}

