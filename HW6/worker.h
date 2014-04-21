/*
* Christopher Sorenson
* csorens2
*/
#ifndef WORKER_H_
#define WORKER_H_

void writeToMemory(int pos, int value); //Helper to write to array in shared memory
int readFromMemory(int pos); //Helper for getting value from array in shared memory

#endif