/*
* Christopher Sorenson
* csorens2
*/
#ifndef MESSAGE_H_
#define MESSAGE_H_

struct worker_message{
	long mtype; //1 = Done Message
				//2 = Error Message
				//3 = Text Message
	int workerID;
	int changedBuffer;
	int initialBufferValue;
	int finalBufferValue;
};

#endif