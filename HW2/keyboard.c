#include <stdio.h>
#include <signal.h>
#include <thread>
#include <chrono>
#include <iostream>
#include <stdlib.h>
#include <setjmp.h>


int increment;
sigjmp_buf jmpbuff;

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
	signal(2,keyboardInterrupHandler);

	sigsetjmp(jmpbuff,1);
	
	int localCounter = 0;
	increment = 1;
	printf("Starting Count \n");
	while(true)
	{
		printf("Current Counter: %d \n",localCounter);
		localCounter += increment;
		std::this_thread::sleep_for(std::chrono::seconds(nSleep));
	}
}

