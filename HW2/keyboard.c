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
			return;
		}
		else if(input == 4)
			_longjmp(jmpbuff,0);
		else
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
	printf("Csorens2\n");
	//Argument Checker
	if(argc < 2)
	{
		printf("Insufficient Arguments. Exiting \n");
		return 0;
	}
	int nSleep = atoi(argv[1]);
	if(nSleep < 1)
	{
		printf("Bad sleep amount. Exiting \n");
		return 0;
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
	
	//Setup jump and start loop
	sigsetjmp(jmpbuff,1);
	int counter = 0;
	increment = 1;
	printf("Starting Count \n");
	while(true)
	{

		/* Taken Out for Third Stage
		printf("Current Counter: %d \n",counter);*/
		counter += increment;
		printf("words[%d] = 0x%x = %d",counter,words[counter],words[counter]);
		if(isprint(words[counter]))
			printf(" = %c", words[counter]);
		offset = 0;
		printf("1.0/ %d = %f \n",(words[counter] + offset), 1.0/(words[counter] + offset));

		time_t start = time(NULL);
		sleep(nSleep);
		printf("Time Slept: %d \n",time(NULL) - start);
	}
}

