#include "KernelEv.h"
#include "SCHEDULE.H"
#include "Context.h"
#include "IVTEntry.h"

KernelEv::KernelEv(unsigned char ivtNo) {
	creator=(PCB*)PCB::running;
	value=0;
	blockedPCB=1;					// not blocked
	entry=ivtNo;
	ivtEntry=IVTEntry::ivtSave;
	ivtEntry->kv=this;
}

void KernelEv::wait() {
	if(PCB::running==creator) {

		if(value==1)
			value=0;
		else {
			creator->stanje=blocked;
			blockedPCB=0;

			dispatch();
#ifndef BCC_BLOCK_IGNORE
			asm cli;
#endif
		}
	}

}

void KernelEv::signal() {
	if(blockedPCB==1){
		value=1;
	}
	else {
		creator->stanje=ready;
		blockedPCB=1;					
		Scheduler::put(creator);
	}
}

KernelEv::~KernelEv() {}

