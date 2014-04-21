/*
* Christopher Sorenson
* csorens2
*/
#ifndef MESSAGE_H_
#define MESSAGE_H_

struct worker_message{
	long mtype; //1 = Hello Message
				//2 = Goodbye Message
				//3 = Error Message
				//4 = Text Message
	int workerID;
	double sleepTime;
};

#endif