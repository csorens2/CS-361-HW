/*
* Christopher Sorenson
* csorens2
*/

#ifndef MYCLASS_H
#define MYCLASS_H
class MyClass {
	public:

	char myclassClass, myclassClassArray[14],
		* myclassClassPtr, myclassInitClass,
		myclassInitClassArray[14], * myclassInitClassPtr; 

	static float myclassStaticClass,
		myclassStaticClassArray[14],
		* myclassStaticClassPtr, myclassStaticInitClass,
		myclassStaticInitClassArray[14],
		* myclassStaticInitClassPtr; 

	MyClass();
	double method( char methodArg, char * methodArgPtr, 
	 				char & methodArgRef ); 
	static double staticMethod( char staticMethodArg,
								char * staticMethodArgPtr,
								char & staticMethodArgRef); 
};
#endif

