#include "KernSem.h"
#include "Context.h"
#include "ListSem.h"
#include "SCHEDULE.H"

int KernelSem::Id = 0;
ListSem* KernelSem::allSems = new ListSem();

KernelSem::KernelSem(int init) {
	value = init;
	id=Id++;
	blockedList = new ListPCB();
}

int KernelSem::waitSem(unsigned int maxTimeToWait) {
	value=value-1;

	PCB::running->waitMax=(int)maxTimeToWait;
	PCB::running->pocMax=(int)maxTimeToWait;

	if(value<0) {
		PCB::running->stanje=blocked;
		blockedList->addPCB((PCB*)PCB::running);

		Context::lockFlag=1;
		dispatch();
		Context::lockFlag=0;
	}

	if(PCB::running->waitMax<=0 && PCB::running->pocMax > 0) {
		return 0;
	}
	return 1;
}

int KernelSem::signalSem(int n) {
	if(value<0) {
		if(n==0) {
			value=value+1;
			helper();
			return 0;
		}
		else if(n>0) {
			value=value+n;
			if(value>0) {
				for(int i=0; i<(n-value); i++)
					helper();
				return value;
			}
			else {
				for(int i=0; i<n; i++)
					helper();
				return n;
			}
		}
		else if(n<0) {
			return n;
		}
	}
	if(n==0)
		value=value+1;
	else if(n<0)
		return n;
	else
		value=value+n;
	return 0;
}

void KernelSem::helper() {
	PCB* p=0;
	if(blockedList!=0) {
	p=blockedList->removePCB();
	if(p!=0) {
		p->stanje=ready;
		Scheduler::put(p);
	}
	}
}

KernelSem::~KernelSem() {
	if(blockedList!=0)
		delete blockedList;
}


