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
	fprintf(stderr, "Hello from generate. Ndata = %d\n", atoi(argv[0]));
	sleep(1);
	fprintf(stderr, "Enter an integer\n");
	char buffer[500];
	cin >> buffer;
	printf("%s",buffer);
	sleep(1);
	fflush(stdout);
	fclose(stdout);
	exit(atoi(argv[0]) + atoi(buffer));
}
