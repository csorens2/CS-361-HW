/*
* Christopher Sorenson
* Csorens2
*/
#include <stdio.h>
#include "func2C.h"

char func2CHello[] = "Hello", * func2CWorld = "World";

char func2CGlobal, func2CGlobalArray[19], * func2CGlobalPtr,
	func2CInitGlobal = 19, func2CInitGlobalArray[19] = {19},
	* func2CInitGlobalPtr = & func2CInitGlobal;

extern char mainCGlobal, mainCGlobalArray[], * mainCGlobalPtr,
			mainCInitGlobal, mainCInitGlobalArray[19],
			* mainCInitGlobalPtr;

static float func2CStaticGlobal, func2CStaticGlobalArray[19],
		* func2CStaticGlobalPtr,
		func2CStaticInitGlobal = 19,
		func2CStaticInitGlobalArray[19] = {19},
		* func2CStaticInitGlobalPtr = &
		func2CStaticInitGlobal; 

//Initilize global variables
void initGlobals2()
{
	func2CGlobal = 19, func2CStaticGlobal = 19; 
	func2CGlobalPtr = &func2CGlobal, func2CStaticGlobalPtr = &func2CStaticGlobal;
	for(int i = 0; i < 19; i++)
	{
		func2CGlobalArray[i] = 19;
		func2CStaticGlobalArray[i] = 19;
	}
}

static double func3C(char func3C_arg1, char *func3C_arg2)
{
	float func3CLocal, func3CLocalArray[19], * func3CLocalPtr,
			func3CInitLocal = 19, func3CInitLocalArray[19] = {19},
			* func3CInitLocalPtr = & func3CInitLocal;
	static float func3CStaticLocal, func3CStaticLocalArray[19],
					* func3CStaticLocalPtr,
					func3CStaticInitLocal = 19,
					func3CStaticInitLocalArray[19] = {19},
					* func3CStaticInitLocalPtr = &
					func3CStaticInitLocal; 

	//Non-declarations
	printf("%s %s from func3C\n",func2CHello, func2CWorld);
	
	//Initialize variables
	func3CLocal = 19, func3CLocalPtr = & func3CLocal;
	for(int i = 0; i < 19; i++)
		func3CLocalArray[i] = 19;
	func3CStaticLocal = 19, func3CStaticLocalPtr = & func3CStaticLocal;
	for(int i = 0; i < 19; i++)
		func3CStaticLocalArray[i] = 19;
	//Add up values
	int total = 0;
	//First local variables
	total += func3CLocal +  *func3CLocalPtr + func3CInitLocal + *func3CInitLocalPtr + 
				func3CStaticLocal + *func3CStaticLocalPtr + func3CStaticInitLocal + 
				*func3CStaticInitLocalPtr;
	for(int i = 0; i < 19; i++)
	{
		total += func3CLocalArray[i] + func3CInitLocalArray[i] + 
					func3CStaticLocalArray[i] + func3CStaticInitLocalArray[i];
	}
	//Next globals
	total += func2CGlobal + *func2CGlobalPtr + func2CInitGlobal + *func2CInitGlobalPtr + 
			func2CStaticGlobal + *func2CStaticGlobalPtr + func2CStaticInitGlobal + 
			*func2CStaticInitGlobalPtr;
	for(int i = 0; i < 19; i++)
	{
		total += func2CGlobalArray[i] + func2CInitGlobalArray[i] + 
				func2CStaticGlobalArray[i] + func2CStaticInitGlobalArray[i];
	}	
	return (double)total;
}

double func2C(char func2C_arg1, char * func1C_arg2)
{
	float func2CLocal, func2CLocalArray[19], * func2CLocalPtr,
		func2CInitLocal = 19, func2CInitLocalArray[19] = {19},
		* func2CInitLocalPtr = & func2CInitLocal;
	static float func2CStaticLocal, func2CStaticLocalArray[19],
				* func2CStaticLocalPtr,
				func2CStaticInitLocal = 19,
				func2CStaticInitLocalArray[19] = {19},
				* func2CStaticInitLocalPtr = &
				func2CStaticInitLocal; 
	printf("%s %s from func2C\n",func2CHello, func2CWorld);	
	//Make sure globals are ready
	initGlobals2();
	//Initialize variables
	func2CLocal = 19, func2CLocalPtr = & func2CLocal;
	for(int i = 0; i < 19; i++)
		func2CLocalArray[i] = 19;
	func2CStaticLocal = 19, func2CStaticLocalPtr = & func2CStaticLocal;
	for(int i = 0; i < 19; i++)
		func2CStaticLocalArray[i] = 19;
	//Add up values
	int total = 0;
	//First local variables
	total += func2CLocal +  *func2CLocalPtr + func2CInitLocal + *func2CInitLocalPtr + 
				func2CStaticLocal + *func2CStaticLocalPtr + func2CStaticInitLocal + 
				*func2CStaticInitLocalPtr;
	for(int i = 0; i < 19; i++)
	{
		total += func2CLocalArray[i] + func2CInitLocalArray[i] + 
					func2CStaticLocalArray[i] + func2CStaticInitLocalArray[i];
	}
	//Next globals
	total += func2CGlobal + *func2CGlobalPtr + func2CInitGlobal + *func2CInitGlobalPtr + 
			func2CStaticGlobal + *func2CStaticGlobalPtr + func2CStaticInitGlobal + 
			*func2CStaticInitGlobalPtr;
	for(int i = 0; i < 19; i++)
	{
		total += func2CGlobalArray[i] + func2CInitGlobalArray[i] + 
				func2CStaticGlobalArray[i] + func2CStaticInitGlobalArray[i];
	}
	total += func3C(func2CGlobal, &func2CGlobal);
	return (double)total;
}
