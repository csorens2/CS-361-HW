/*
* Christopher Sorenson
* csorens2
*/
#include "calculate.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
using namespace std;

int main(int argc, char** argv)
{
	int 	genPipe[2], displayPipe[2];
	char 	*nData, *nRows, *nCols;

	printf("Christopher Sorenson \nCSorens2\n");

	if(argc < 4)
		errorHandler(0);
	nData = argv[1];
	nRows = argv[2];
	nCols = argv[3];
	printf("Hello from Calculate. nData = %d. nRows = %d. nCols = %d\n",
			atoi(nData),atoi(nRows),atoi(nCols));

	if(pipe(genPipe))
		errorHandler(1);
	if(pipe(displayPipe))
		errorHandler(2);

	int dispPid = fork();
	if(dispPid < 0)
		errorHandler(3);
	if(dispPid == 0) //Child Process
	{
		close(genPipe[0]);
		close(genPipe[1]);
		close(displayPipe[1]);
		dup2(displayPipe[0],0);
		close(displayPipe[0]);
		execl("./display", nRows, nCols, (char*)0);
		errorHandler(5);
	}

	int genPid = fork();
	if(genPid < 0)
		errorHandler(4);
	if(genPid == 0)//Child process
	{
		close(displayPipe[0]);
		close(displayPipe[1]);
		close(genPipe[0]);
		dup2(genPipe[1],1);
		close(genPipe[1]);
		execl("./generate", nData, (char*)0);
		errorHandler(6);
	}
	
	close(genPipe[1]);
	close(displayPipe[0]);

	char buffer[500];
	FILE *stream = fdopen(genPipe[0], "r");
	while(1)
	{
		if(fscanf(stream,"%s",buffer) != EOF)
		{
			FILE *stream2 = fdopen(displayPipe[1],"w");
			fwrite(buffer,sizeof(char),500,stream2);
			fclose(stream2);
			int dispExit;
			int genExit;
			waitpid(dispPid, &dispExit, 0);
			waitpid(genPid, &genExit, 0);
			printf("Display exited with %d \n",WEXITSTATUS(dispExit));
			printf("Generate exited with %d \n",WEXITSTATUS(genExit));
			close(displayPipe[1]);
			close(genPipe[0]);
			exit(0);
		}
	}
}

void errorHandler(int x)
{
	if(x == 0)//Not enough arguments
		printf("Insufficient Arguments\n");	
	if(x == 1)
		printf("genPipe failed \n");
	if(x == 2)
		printf("displayPipe failed \n");
	if(x == 3)
		printf("Display fork failed\n");
	if(x == 4)
		printf("Generate fork failed\n");
	if(x == 5)
		printf("Display failed to launch\n");
	if(x == 6)
		printf("Generate failed to launch\n");
	exit(-1);
}
