/*
* Christopher Sorenson
* csorens2
*/


#include "myClass.h"
char myClassHello[] = "Hello", * myClassWorld = "World";

char myClassGlobal, myClassGlobalArray[14], * myClassGlobalPtr,
		myClassInitGlobal = 14, myClassInitGlobalArray[14] = {14},
		* myClassInitGlobalPtr = & myClassInitGlobal;

static float myClassStaticGlobal, myClassStaticGlobalArray[14],
			* myClassStaticGlobalPtr,
			myClassStaticInitGlobal = 14,
			myClassStaticInitGlobalArray[14] = {14},
			* myClassStaticInitGlobalPtr = &
			myClassStaticInitGlobal; 

MyClass::MyClass()
{
}

void initGlobals4()
{
	myClassGlobal = 19, myClassStaticGlobal = 19; 
	myClassGlobalPtr = &myClassGlobal, myClassStaticGlobalPtr = &myClassStaticGlobal;
	for(int i = 0; i < 19; i++)
	{
		myClassGlobalArray[i] = 19;
		myClassStaticGlobalArray[i] = 19;
	}

}

double MyClass::method( char methodArg, char * methodArgPtr, 
 				char & methodArgRef )
{
	initGlobals4();
	int total = 0;
	total += myClassGlobal + *myClassGlobalPtr + myClassInitGlobal + *myClassInitGlobalPtr + 
			myClassStaticGlobal + *myClassStaticGlobalPtr + myClassStaticInitGlobal + 
			*myClassStaticInitGlobalPtr;
	for(int i = 0; i < 19; i++)
	{
		total += myClassGlobalArray[i] + myClassInitGlobalArray[i] + 
				myClassStaticGlobalArray[i] + myClassStaticInitGlobalArray[i];
	}	
	return (double)total;
}

double MyClass::staticMethod( char staticMethodArg,
							char * staticMethodArgPtr,
							char & staticMethodArgRef)
{
	initGlobals4();
	int total = 0;
	total += myClassGlobal + *myClassGlobalPtr + myClassInitGlobal + *myClassInitGlobalPtr + 
			myClassStaticGlobal + *myClassStaticGlobalPtr + myClassStaticInitGlobal + 
			*myClassStaticInitGlobalPtr;
	for(int i = 0; i < 19; i++)
	{
		total += myClassGlobalArray[i] + myClassInitGlobalArray[i] + 
				myClassStaticGlobalArray[i] + myClassStaticInitGlobalArray[i];
	}	
	return (double)total;
}
