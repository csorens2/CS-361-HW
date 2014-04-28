/*
* Christopher Sorenson
* csorens2
*/
#include "shell.h"
using namespace std;

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <vector>
#include <sys/wait.h>
#include <sys/types.h>

#include <unistd.h>

char input[40];
char** argv;


int main(int argc, char** argv)
{
	printf("Christopher Sorenson \ncsorens2 \n");
	printf("\nWelcome to the Shell\n");

	//Start shell 
	while(1)
	{

start:
		printf("\nCommand?\n");

		//Get the string from the user and turn it into a c-string
		string fromConsole;
		getline(cin,fromConsole);
		strcpy(input,fromConsole.c_str());

		//Tokenize the string and turn it into a vector of char*
		char * token;
		vector<char*> argVec;
		token = strtok(input, " ");
		while(token != NULL)
		{
			argVec.push_back(token);
			token = strtok (NULL, " ");
		}

		//Assign argv pointers to vector data
		for(int i = 0; i < argVec.size(); i++)
			argv[i] = argVec[i];

		// User asked for stats. Print it out then get another command
		if(!strcmp((argv[0]),"stats"))
		{	
			struct rusage usage;
			getrusage(RUSAGE_CHILDREN,&usage);
			double userTime = usage.ru_utime.tv_sec;
			double userTime2 = usage.ru_utime.tv_usec;
			double systemTime = usage.ru_stime.tv_sec;
			double systemTime2 = usage.ru_stime.tv_usec;

			printf("Total Usertime %f\n",userTime + (userTime2 / 1000000));
			printf("Total Systemtime %f\n",systemTime + (systemTime2 / 1000000));
			goto start;
		}

		//Exit the program if they input exit
		if(!strcmp((argv[0]),"exit"))
			return 0;
		
		//Execute command sent to shell
		int childPid = fork();
		if(childPid == 0) // Child runs the program
			execvp(argv[0],argv);

		//Wait for the program to exit. Then print out time spent
		int exitCode;
		struct rusage usage;
		wait4(childPid,&exitCode,0,&usage);
		
		double userTime = usage.ru_utime.tv_sec;
		double userTime2 = usage.ru_utime.tv_usec;
		double systemTime = usage.ru_stime.tv_sec;
		double systemTime2 = usage.ru_stime.tv_usec;

		printf("\nProgram %s exited with code %d\n",argv[0],exitCode);
		printf("Usertime %f\n",userTime + (userTime2 / 1000000));
		printf("Systemtime %f\n",systemTime + (systemTime2 / 1000000));
	}
}
