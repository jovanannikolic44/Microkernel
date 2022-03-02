/*
 * semaphor.cpp
 *
 *  Created on: Apr 20, 2020
 *      Author: OS1
 */

#include "Semaphor.h"
#include "Context.h"
#include "ListSem.h"


Semaphore::Semaphore(int init) {
	Context::lockFlag = 0;
	myImpl = new KernelSem(init);
	Context::lockFlag = 1;
	if(Context::wantChange)
		dispatch();

	Context::lockFlag=0;
	KernelSem::allSems->addSem(myImpl);
	Context::lockFlag=1;
	if(Context::wantChange)
		dispatch();

}

int Semaphore::wait(Time maxTimeToWait) {
	Context::lockFlag=0;
	int ret;
	ret=myImpl->waitSem(maxTimeToWait);
	Context::lockFlag=1;
	if(Context::wantChange)
		dispatch();
	return ret;
}

int Semaphore::signal(int n) {
	Context::lockFlag=0;
	int ret;
	ret=myImpl->signalSem(n);
	Context::lockFlag=1;
	if(Context::wantChange)
		dispatch();
	return ret;
}

int Semaphore::val() const {
	return myImpl->value;
}

Semaphore::~Semaphore() {
	Context::lockFlag = 0;
	if(myImpl!=0)
		delete myImpl;
	Context::lockFlag = 1;
}


