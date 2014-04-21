/*
* Christopher Sorenson
* csorens2
*/
#ifndef MESSAGE_H_
#define MESSAGE_H_

struct worker_message{
	long mtype; //1 = Done Message
				//2 = Read error Message
				//3 = Write error message
	int workerID;
	int changedBuffer;
	int initialBufferValue;
	int finalBufferValue;
};

#endif