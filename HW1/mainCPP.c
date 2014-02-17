/*
* Christopher Sorenson
* csorens2
*/
#include <stdio.h>
#include "myClass.h"
#include "func2CPP.h"

char mainCPPHello[] = "Hello", * mainCPPWorld = "World";

char mainCPPGlobal, mainCPPGlobalArray[19], * mainCPPGlobalPtr,
		mainCPPInitGlobal = 19, mainCPPInitGlobalArray[19] = {19},
		* mainCPPInitGlobalPtr = & mainCPPInitGlobal;

static float mainCPPStaticGlobal, mainCPPStaticGlobalArray[19],
			* mainCPPStaticGlobalPtr,
			mainCPPStaticInitGlobal = 19,
			mainCPPStaticInitGlobalArray[19] = {19},
			* mainCPPStaticInitGlobalPtr = &
			mainCPPStaticInitGlobal; 

MyClass globalMyClass1 = MyClass(), globalMyClass2;

void initGlobals()
{
	mainCPPGlobal = 19, mainCPPStaticGlobal = 19; 
	mainCPPGlobalPtr = &mainCPPGlobal;
	mainCPPStaticGlobalPtr = &mainCPPStaticGlobal;
	globalMyClass1;
	globalMyClass2;
	for(int i = 0; i < 19; i++)
	{
		mainCPPGlobalArray[i] = 19;
	}
		
}

double func1CPP( char func1CPP_arg1, char * func1CPP_arg2,
					char & func1CPP_arg3)
{
	float func1CPPLocal, func1CPPLocalArray[19], * func1CPPLocalPtr,
			func1CPPInitLocal = 19, func1CPPInitLocalArray[19] = {19},
			* func1CPPInitLocalPtr = & func1CPPInitLocal;

	static float func1CPPStaticLocal, func1CPPStaticLocalArray[19],
					* func1CPPStaticLocalPtr,
					func1CPPStaticInitLocal = 19,
					func1CPPStaticInitLocalArray[19] = {19},
					* func1CPPStaticInitLocalPtr = &
					func1CPPStaticInitLocal; 

	printf("%s %s from func1CPP\n",mainCPPHello, mainCPPWorld);
	//Initialize variables
	func1CPPLocal = 19, func1CPPLocalPtr = & func1CPPLocal;
	for(int i = 0; i < 19; i++)
		func1CPPLocalArray[i] = 19;
	func1CPPStaticLocal = 19, func1CPPStaticLocalPtr = & func1CPPStaticLocal;
	for(int i = 0; i < 19; i++)
		func1CPPStaticLocalArray[i] = 19;
	//Add up values
	int total = 0;
	//First local variables
	total += func1CPPLocal +  *func1CPPLocalPtr + func1CPPInitLocal + *func1CPPInitLocalPtr + 
				func1CPPStaticLocal + *func1CPPStaticLocalPtr + func1CPPStaticInitLocal + 
				*func1CPPStaticInitLocalPtr;
	for(int i = 0; i < 19; i++)
	{
		total += func1CPPLocalArray[i] + func1CPPInitLocalArray[i] + 
					func1CPPStaticLocalArray[i] + func1CPPStaticInitLocalArray[i];
	}
	//Next globals
	total += mainCPPGlobal + *mainCPPGlobalPtr + mainCPPInitGlobal + *mainCPPInitGlobalPtr + 
			mainCPPStaticGlobal + *mainCPPStaticGlobalPtr + mainCPPStaticInitGlobal + 
			*mainCPPStaticInitGlobalPtr;
	for(int i = 0; i < 19; i++)
	{
		total += mainCPPGlobalArray[i] + mainCPPInitGlobalArray[i] + 
				mainCPPStaticGlobalArray[i] + mainCPPStaticInitGlobalArray[i];
	}	
	return (double)total;			
		
}

int main(int argc, char **argv)
{
	float mainLocal, mainLocalArray[19], * mainLocalPtr,
		mainInitLocal = 19, mainInitLocalArray[19] = {19},
		* mainInitLocalPtr = & mainInitLocal;
	static float mainStaticLocal, mainStaticLocalArray[19],
				* mainStaticLocalPtr,
				mainStaticInitLocal = 19,
				mainStaticInitLocalArray[19] = {19},
				* mainStaticInitLocalPtr = &
				mainStaticInitLocal; 

	MyClass localMainMyClass1, localMainMyClass2;

	printf("Christopher Sorenson csorens2\n");
	printf("%s %s from main\n",mainCPPHello, mainCPPWorld);
	//Make sure globals are ready
	initGlobals();

	//Initialize local variables
	mainLocal = 19, mainLocalPtr = & mainLocal;
	for(int i = 0; i < 19; i++)
		mainLocalArray[i] = 19;
	mainStaticLocal = 19, mainStaticLocalPtr = & mainStaticLocal;
	for(int i = 0; i < 19; i++)
		mainStaticLocalArray[i] = 19;
	//Add up values
	int total = 0;
	//First local variables
	total += mainLocal +  *mainLocalPtr + mainInitLocal + *mainInitLocalPtr + 
				mainStaticLocal + *mainStaticLocalPtr + mainStaticInitLocal + 
				*mainStaticInitLocalPtr;
	for(int i = 0; i < 19; i++)
	{
		total += mainLocalArray[i] + mainInitLocalArray[i] + 
					mainStaticLocalArray[i] + mainStaticInitLocalArray[i];
	}
	//Next globals
	total += mainCPPGlobal + *mainCPPGlobalPtr + mainCPPInitGlobal + *mainCPPInitGlobalPtr + 
			mainCPPStaticGlobal + *mainCPPStaticGlobalPtr + mainCPPStaticInitGlobal + 
			*mainCPPStaticInitGlobalPtr;
	for(int i = 0; i < 19; i++)
	{
		total += mainCPPGlobalArray[i] + mainCPPInitGlobalArray[i] + 
				mainCPPStaticGlobalArray[i] + mainCPPStaticInitGlobalArray[i];
	}	
	//Grab values from other functions
	total += func1CPP(mainCPPGlobal, & mainCPPGlobal, mainCPPGlobal);
	total += func2CPP(mainCPPGlobal, & mainCPPGlobal, mainCPPGlobal);
	printf("Current total after main, func1, func2, and func3 and func2(2): %d \n",total);
	//Add in globals from my class
}

