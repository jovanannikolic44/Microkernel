#ifndef SEMAPHOR_H_
#define SEMAPHOR_H_
#include "KernSem.h"

typedef unsigned int Time;

class KernelSem;

class Semaphore {
public:
	Semaphore(int init=1);
	virtual ~Semaphore();

	virtual int wait(Time maxTimeToWait);
	virtual int signal(int n=0);

	int val() const;

public:
	KernelSem* myImpl;

};

#endif /* SEMAPHOR_H_ */
