/*
* Christopher Sorenson
* csorens2
*/
#include <stdio.h>
#include "func2C.h"

char mainCHello[] = "Hello", *mainCWorld = "World"; 

char mainCGlobal, mainCGlobalArray[19], * mainCGlobalPtr,
	mainCInitGlobal = 19, mainCInitGlobalArray[19] = {19},
	* mainCInitGlobalPtr = & mainCInitGlobal; 

extern char func2CGlobal, func2CGlobalArray[], * func2CGlobalPtr,
			func2CInitGlobal, func2CInitGlobalArray[],
			* func2CInitGlobalPtr;

static float mainCStaticGlobal, mainCStaticGlobalArray[19],
		* mainCStaticGlobalPtr,
		mainCStaticInitGlobal = 19,
		mainCStaticInitGlobalArray[19] = {19},
		* mainCStaticInitGlobalPtr = &
		mainCStaticInitGlobal; 

void initGlobals()
{
	mainCGlobal = 19, mainCStaticGlobal = 19; 
	mainCGlobalPtr = &mainCGlobal, mainCStaticGlobalPtr = &mainCStaticGlobal;
	for(int i = 0; i < 19; i++)
	{
		mainCGlobalArray[i] = 19;
		mainCStaticGlobalArray[i] = 19;
	}
	
}

double func1C(char func1C_arg1, char * func1C_arg2)
{
	float func1CLocal, func1CLocalArray[19], * func1CLocalPtr,
			func1CInitLocal = 19, func1CInitLocalArray[19] = {19},
			* func1CInitLocalPtr = & func1CInitLocal;

	static float func1CStaticLocal, func1CStaticLocalArray[19],
					* func1CStaticLocalPtr,
					func1CStaticInitLocal = 19,
					func1CStaticInitLocalArray[19] = {19},
					* func1CStaticInitLocalPtr = &
					func1CStaticInitLocal; 

	printf("%s %s from func1C\n",mainCHello, mainCWorld);
	//Initialize variables
	func1CLocal = 19, func1CLocalPtr = & func1CLocal;
	for(int i = 0; i < 19; i++)
		func1CLocalArray[i] = 19;
	func1CStaticLocal = 19, func1CStaticLocalPtr = & func1CStaticLocal;
	for(int i = 0; i < 19; i++)
		func1CStaticLocalArray[i] = 19;
	//Add up values
	int total = 0;
	//First local variables
	total += func1CLocal +  *func1CLocalPtr + func1CInitLocal + *func1CInitLocalPtr + 
				func1CStaticLocal + *func1CStaticLocalPtr + func1CStaticInitLocal + 
				*func1CStaticInitLocalPtr;
	for(int i = 0; i < 19; i++)
	{
		total += func1CLocalArray[i] + func1CInitLocalArray[i] + 
					func1CStaticLocalArray[i] + func1CStaticInitLocalArray[i];
	}
	//Next globals
	total += mainCGlobal + *mainCGlobalPtr + mainCInitGlobal + *mainCInitGlobalPtr + 
			mainCStaticGlobal + *mainCStaticGlobalPtr + mainCStaticInitGlobal + 
			*mainCStaticInitGlobalPtr;
	for(int i = 0; i < 19; i++)
	{
		total += mainCGlobalArray[i] + mainCInitGlobalArray[i] + 
				mainCStaticGlobalArray[i] + mainCStaticInitGlobalArray[i];
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
	printf("Christopher Sorenson csorens2\n");
	printf("%s %s from main\n",mainCHello, mainCWorld);
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
	total += mainCGlobal + *mainCGlobalPtr + mainCInitGlobal + *mainCInitGlobalPtr + 
			mainCStaticGlobal + *mainCStaticGlobalPtr + mainCStaticInitGlobal + 
			*mainCStaticInitGlobalPtr;
	for(int i = 0; i < 19; i++)
	{
		total += mainCGlobalArray[i] + mainCInitGlobalArray[i] + 
				mainCStaticGlobalArray[i] + mainCStaticInitGlobalArray[i];
	}	
	total += func1C(mainCGlobal, & mainCGlobal);
	total += func2C(mainCGlobal, & mainCGlobal);
	printf("Current total after main, func1, func2, and func3: %d \n",total);
}
