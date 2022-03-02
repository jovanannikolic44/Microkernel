#include "event.h"
#include "Context.h"
#include "KernelEv.h"

Event::Event(IVTNo ivtNo) {
#ifndef BCC_BLOCK_IGNORE
	asm cli;
#endif
	myImpl=new KernelEv(ivtNo);
#ifndef BCC_BLOCK_IGNORE
	asm sti;
#endif
}

void Event::wait() {
#ifndef BCC_BLOCK_IGNORE
	asm cli;
#endif
	myImpl->wait();
#ifndef BCC_BLOCK_IGNORE
	asm sti;
#endif

}

void Event::signal() {
#ifndef BCC_BLOCK_IGNORE
	asm cli;
#endif
	myImpl->signal();
#ifndef BCC_BLOCK_IGNORE
	asm sti;
#endif
}

Event::~Event() {
#ifndef BCC_BLOCK_IGNORE
	asm cli;
#endif
	if(myImpl != 0)
		delete myImpl;
#ifndef BCC_BLOCK_IGNORE
	asm sti;
#endif
}

