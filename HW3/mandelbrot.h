/*
* Christopher Sorenson
* csorens2
*/
#ifndef MANDELBROT_H_
#define MANDELBROT_H_

static void forkProcesses();//Also sets up the respective processes pipes
static void setupQueues();
static void childSignalHandler(int sig);

#endif
