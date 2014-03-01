/*
* Christopher Sorenson
* csorens2
*/
#include "mandelbrot.h"
#include <stdio.h>
#include <sys/wait.h>
#include <thread>
#include <signal.h>
#include <iostream>

int childpid = -1;

int main(int argc, char** argv)
{
	printf("Chris Sorenson \ncsorens2 \n");
	childpid = fork();
	if(childpid == 0) //Children processes
	{
		childpid = fork();
		if(childpid == 0) //First child process
		{
		}
		else //Second Child Process
		{
		}
	}
	else //Parent Process
	{
			
	}
}
