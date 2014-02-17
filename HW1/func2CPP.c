/*
* Christopher Sorenson
* csorens2
*/
#include <stdio.h>
#include "myClass.h"
#include "func2C.h"
char func2CPPHello[] = "Hello", * func2CPPWorld = "World";

char func2CPPGlobal, func2CPPGlobalArray[19], * func2CPPGlobalPtr,
		func2CPPInitGlobal = 19, func2CPPInitGlobalArray[19] = {19},
		* func2CPPInitGlobalPtr = & func2CPPInitGlobal;

static float func2CPPStaticGlobal, func2CPPStaticGlobalArray[19],
			* func2CPPStaticGlobalPtr,
			func2CPPStaticInitGlobal = 19,
			func2CPPStaticInitGlobalArray[19] = {19},
			* func2CPPStaticInitGlobalPtr = &
			func2CPPStaticInitGlobal; 

MyClass globalMyClass3, globalMyClass4;

//Initilize global variables
void initGlobals2()
{
	func2CPPGlobal = 19, func2CPPStaticGlobal = 19; 
	func2CPPGlobalPtr = &func2CPPGlobal, func2CPPStaticGlobalPtr = &func2CPPStaticGlobal;
	for(int i = 0; i < 19; i++)
	{
		func2CPPGlobalArray[i] = 19;
		func2CPPStaticGlobalArray[i] = 19;
	}
}	

static double func3CPP( char func3CPP_arg1, char * func3CPP_arg2,
							char & func3CPP_arg3 )
{
	float func3CPPLocal, func3CPPLocalArray[19], * func3CPPLocalPtr,
			func3CPPInitLocal = 19, func3CPPInitLocalArray[19] = {19},
			* func3CPPInitLocalPtr = & func3CPPInitLocal;
	static float func3CPPStaticLocal, func3CPPStaticLocalArray[19],
					* func3CPPStaticLocalPtr,
					func3CPPStaticInitLocal = 19,
					func3CPPStaticInitLocalArray[19] = {19},
					* func3CPPStaticInitLocalPtr = &
					func3CPPStaticInitLocal; 

	//Non-declarations
	printf("%s %s from func3CPP\n",func2CPPHello, func2CPPWorld);
	
	//Initialize variables
	func3CPPLocal = 19, func3CPPLocalPtr = & func3CPPLocal;
	for(int i = 0; i < 19; i++)
		func3CPPLocalArray[i] = 19;
	func3CPPStaticLocal = 19, func3CPPStaticLocalPtr = & func3CPPStaticLocal;
	for(int i = 0; i < 19; i++)
		func3CPPStaticLocalArray[i] = 19;
	//Add up values
	int total = 0;
	//First local variables
	total += func3CPPLocal +  *func3CPPLocalPtr + func3CPPInitLocal + *func3CPPInitLocalPtr + 
				func3CPPStaticLocal + *func3CPPStaticLocalPtr + func3CPPStaticInitLocal + 
				*func3CPPStaticInitLocalPtr;
	for(int i = 0; i < 19; i++)
	{
		total += func3CPPLocalArray[i] + func3CPPInitLocalArray[i] + 
					func3CPPStaticLocalArray[i] + func3CPPStaticInitLocalArray[i];
	}
	//Next globals
	total += func2CPPGlobal + *func2CPPGlobalPtr + func2CPPInitGlobal + *func2CPPInitGlobalPtr + 
			func2CPPStaticGlobal + *func2CPPStaticGlobalPtr + func2CPPStaticInitGlobal + 
			*func2CPPStaticInitGlobalPtr;
	for(int i = 0; i < 19; i++)
	{
		total += func2CPPGlobalArray[i] + func2CPPInitGlobalArray[i] + 
				func2CPPStaticGlobalArray[i] + func2CPPStaticInitGlobalArray[i];
	}	
	return (double)total;
}

double func2CPP( char * func2BCPP_arg1, char & func2BCPP_arg2,
					char func2BCPP_arg3 )
{
	float func2CPPLocal, func2CPPLocalArray[19], * func2CPPLocalPtr,
			func2CPPInitLocal = 19, func2CPPInitLocalArray[19] = {19},
			* func2CPPInitLocalPtr = & func2CPPInitLocal;
	static float func2CPPStaticLocal, func2CPPStaticLocalArray[19],
					* func2CPPStaticLocalPtr,
					func2CPPStaticInitLocal = 19,
					func2CPPStaticInitLocalArray[19] = {19},
					* func2CPPStaticInitLocalPtr = &
					func2CPPStaticInitLocal; 

	//Non-declarations
	printf("%s %s from func2CPP\n",func2CPPHello, func2CPPWorld);
	
	//Initialize variables
	func2CPPLocal = 19, func2CPPLocalPtr = & func2CPPLocal;
	for(int i = 0; i < 19; i++)
		func2CPPLocalArray[i] = 19;
	func2CPPStaticLocal = 19, func2CPPStaticLocalPtr = & func2CPPStaticLocal;
	for(int i = 0; i < 19; i++)
		func2CPPStaticLocalArray[i] = 19;
	//Add up values
	int total = 0;
	//First local variables
	total += func2CPPLocal +  *func2CPPLocalPtr + func2CPPInitLocal + *func2CPPInitLocalPtr + 
				func2CPPStaticLocal + *func2CPPStaticLocalPtr + func2CPPStaticInitLocal + 
				*func2CPPStaticInitLocalPtr;
	for(int i = 0; i < 19; i++)
	{
		total += func2CPPLocalArray[i] + func2CPPInitLocalArray[i] + 
					func2CPPStaticLocalArray[i] + func2CPPStaticInitLocalArray[i];
	}
	//Next globals
	total += func2CPPGlobal + *func2CPPGlobalPtr + func2CPPInitGlobal + *func2CPPInitGlobalPtr + 
			func2CPPStaticGlobal + *func2CPPStaticGlobalPtr + func2CPPStaticInitGlobal + 
			*func2CPPStaticInitGlobalPtr;
	for(int i = 0; i < 19; i++)
	{
		total += func2CPPGlobalArray[i] + func2CPPInitGlobalArray[i] + 
				func2CPPStaticGlobalArray[i] + func2CPPStaticInitGlobalArray[i];
	}	
	return (double)total;

}

//This is the func2 that is called from main
double func2CPP( char func2CPP_arg1, char * func2CPP_arg2,
					char & func2CPP_arg3 )
{
	initGlobals2();
	float func2CPPLocal, func2CPPLocalArray[19], * func2CPPLocalPtr,
			func2CPPInitLocal = 19, func2CPPInitLocalArray[19] = {19},
			* func2CPPInitLocalPtr = & func2CPPInitLocal;
	static float func2CPPStaticLocal, func2CPPStaticLocalArray[19],
					* func2CPPStaticLocalPtr,
					func2CPPStaticInitLocal = 19,
					func2CPPStaticInitLocalArray[19] = {19},
					* func2CPPStaticInitLocalPtr = &
					func2CPPStaticInitLocal; 
	//Non-declarations
	printf("%s %s from func2CPP\n",func2CPPHello, func2CPPWorld);
	
	//Initialize variables
	func2CPPLocal = 19, func2CPPLocalPtr = & func2CPPLocal;
	for(int i = 0; i < 19; i++)
		func2CPPLocalArray[i] = 19;
	func2CPPStaticLocal = 19, func2CPPStaticLocalPtr = & func2CPPStaticLocal;
	for(int i = 0; i < 19; i++)
		func2CPPStaticLocalArray[i] = 19;
	//Add up values
	int total = 0;
	//First local variables
	total += func2CPPLocal +  *func2CPPLocalPtr + func2CPPInitLocal + *func2CPPInitLocalPtr + 
				func2CPPStaticLocal + *func2CPPStaticLocalPtr + func2CPPStaticInitLocal + 
				*func2CPPStaticInitLocalPtr;
	for(int i = 0; i < 19; i++)
	{
		total += func2CPPLocalArray[i] + func2CPPInitLocalArray[i] + 
					func2CPPStaticLocalArray[i] + func2CPPStaticInitLocalArray[i];
	}
	//Next globals
	total += func2CPPGlobal + *func2CPPGlobalPtr + func2CPPInitGlobal + *func2CPPInitGlobalPtr + 
			func2CPPStaticGlobal + *func2CPPStaticGlobalPtr + func2CPPStaticInitGlobal + 
			*func2CPPStaticInitGlobalPtr;
	for(int i = 0; i < 19; i++)
	{
		total += func2CPPGlobalArray[i] + func2CPPInitGlobalArray[i] + 
				func2CPPStaticGlobalArray[i] + func2CPPStaticInitGlobalArray[i];
	}	
	//Next we get the values from the two other functions
	total += func3CPP(func2CPPGlobal, &func2CPPGlobal, func2CPPGlobal);
	total += func2CPP(&func2CPPGlobal, func2CPPGlobal, func2CPPGlobal);
	//Finally we get the myclass values
	return (double)total;
}
