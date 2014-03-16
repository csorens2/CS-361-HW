#ifndef STRUCTURES_H_
#define STRUCTURES_H_

struct done_msg{
	long mtype;
	int child;
};

struct filename_msg{
	long mtype;
	char filename[20];
	double info[7];
};
#endif
