#include "Thread.h"
#include "ListPCB.h"
#include "SCHEDULE.h"
#include "Context.h"

Thread::Thread(StackSize stackSize, Time timeSlice) {
	if(stackSize > 65535) {
		stackSize = 65535;
	}
	StackSize size = stackSize/sizeof(unsigned);
	Time time = timeSlice;
	Context::lockFlag = 0;


	myPCB = new PCB(size, time);

	if(myPCB == 0) {
		cout<<"Error in Thread.cpp";
		Context::lockFlag = 1;
		return;
	}

	myPCB->t=this;

	if(myPCB->t == 0) {
		cout<<"MyPCB->t is null";
		Context::lockFlag = 1;
		return;
	}

	PCB::headP->addPCB(myPCB);


	Context::lockFlag = 1;
	if(Context::wantChange)
		dispatch();
}

void Thread::start() {
	if(myPCB==0) {
		Context::lockFlag = 0;
		cout<<"Error in Thread.cpp, start";
		Context::lockFlag = 1;
		return;
	}

	if(myPCB->stanje == created) {
		myPCB->stanje = ready;
		Scheduler::put(myPCB);
	}
}

void Thread::waitToComplete() {
	Context::lockFlag=0;
	if(PCB::running == 0 || myPCB == 0){
		cout<<"Error in Thread.cpp"<<endl;
		Context::lockFlag=1;
		return;
	}


	if(PCB::running->id == myPCB->id ) {
		Context::lockFlag = 1;
		return;
	}

	if (myPCB->stanje != terminated) {
		PCB::running->stanje = blocked;
		myPCB->wtc->addPCB((PCB*)PCB::running);
		Context::lockFlag=1;
		dispatch();
	}
	else {
		Context::lockFlag=1;
		if(Context::wantChange)
			dispatch();
	}
}

ID Thread::getId() {
	if(myPCB!=0)
		return myPCB->id;
}

Thread* Thread::getThreadById(ID id) {
	Context::lockFlag = 0;
	PCB* nit = 0;
	nit = PCB::headP->getPCBid(id);
	Context::lockFlag = 1;
	if(Context::wantChange)
		dispatch();
	if(nit!=0) {
		Thread* tr = nit->t;
		return tr;

		return 0;
	}
}

ID Thread::getRunningId() {
	if(PCB::running != 0)
		return PCB::running->id;
}

Thread::~Thread() {
	Context::lockFlag = 0;
	delete myPCB;
	Context::lockFlag = 1;
	if(Context::wantChange)
		dispatch();
}

PCB* Thread::getMyPCB() {
	return myPCB;
}


void dispatch() {
#ifndef BCC_BLOCK_IGNORE
	asm cli;
	Context::wantChange=1;
	timer();
	asm sti;
#endif
}




