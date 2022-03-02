/*
 * Thread.h
 *
 *  Created on: Mar 26, 2020
 *      Author: OS1
 */

#ifndef THREAD_H_
#define THREAD_H_
#include <iostream.h>
#include "PCB.h"

typedef unsigned long StackSize;
const StackSize defaultStackSize = 4096;
typedef unsigned Time;
const Time defaultTimeSlice = 2; // default = 2*55ms
typedef int ID;

class PCB;
class ListPCB;

class Thread {
public:
	PCB* myPCB;
protected:
	friend class PCB;
	Thread(StackSize stackSize = defaultStackSize, Time timeSlice = defaultTimeSlice);
	virtual void run() {}
public:
	void start();
	void waitToComplete();
	ID getId();
	static Thread* getThreadById(ID id);
	static ID getRunningId();
	virtual ~Thread();
	PCB* getMyPCB();



};

void dispatch();

#endif

