/*
* Christopher Sorenson
* csorens2
*/
#ifndef MASTER_H_
#define MASTER_H_

int compareDouble(const void *x, const void *y); //Used for sorting
void writeToMemory(int pos, int value); //Helper to write to array in shared memory
int readFromMemory(int pos);  //Helper to get value from array in shared memory
void debugValues(); //Sets parameters to specific values for debugging

#endif