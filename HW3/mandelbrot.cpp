/*
* Christopher Sorenson
* csorens2
*/
#include "mandelbrot.h"
#include "mandelCalc.h"
#include "mandelDisplay.h"

#include <stdio.h>
#include <sys/wait.h>
#include <thread>
#include <signal.h>
#include <iostream>
#include <stdarg.h>


int calcPid = -1, displayPid = -1;

int main(int argc, char** argv)
{
	printf("Chris Sorenson \ncsorens2 \n");

	calcPid = fork();
	if(calcPid == 0) //Launch Calc Process
		execl("./mandelCalc","Hello World", "Testing", (char *) 0);

	displayPid = fork();
	if(displayPid == 0)
		execl("./mandelDisplay","Good Night",(char *) 0);
	
	waitpid(calcPid,NULL,0);
	waitpid(displayPid,NULL,0);
}
