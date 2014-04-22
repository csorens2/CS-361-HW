/*
* Christopher Sorenson
* csorens2
*/
#ifndef MESSAGE_H_
#define MESSAGE_H_

struct worker_message{
	long mtype; //1 = Done Message
				//2 = Read error Message
	int workerID;
	int changedBuffer;
	int initialBufferValue;
	int finalBufferValue;
};

#if defined(__GNU_LIBRARY__) && !defined(_SEM_SEMUN_UNDEFINED) 
/* union semun is defined by including <sys/sem.h> */ 
#else 
/* according to X/OPEN we have to define it ourselves */ 
union semun { 
      int val;                  /* value for SETVAL */ 
      struct semid_ds *buf;     /* buffer for IPC_STAT, IPC_SET */ 
      unsigned short *array;    /* array for GETALL, SETALL */ 
                                /* Linux specific part: */ 
      struct seminfo *__buf;    /* buffer for IPC_INFO */ 
}; 
#endif 


#endif