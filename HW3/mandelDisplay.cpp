/*
* Christopher Sorenson
* csorens2
*/
#include "mandelDisplay.h"
#include <stdio.h>
#include <sys/wait.h>
#include <thread>
#include <signal.h>
#include <iostream>

int main(int argc, char** argv)
{
	char buffer[100];
	fread(buffer, sizeof(char), 16, stdin);

	printf("Hello from display\n");
	printf("And %s circa display\n",buffer);
	//exit(1);
}
