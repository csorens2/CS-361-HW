/*
* Christopher Sorenson
* csorens2
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
using namespace std;

int main(int argc, char** argv)
{
	fprintf(stderr, "Hello from display. NRows = %d. Ncols = %d\n", 
				atoi(argv[0]), atoi(argv[1]));

	char buffer[500];
	while(1)
	{		
		if(fscanf(stdin,"%s",buffer) > 0)
		{
			fprintf(stderr, "Received data\n");
		}
	}
}
