#include "IVTEntry.h"
#include "KernelEv.h"
#include "Context.h"
#include <dos.h>

IVTEntry* IVTEntry::ivtSave=0;

IVTEntry::IVTEntry(int newEntry, pInterrupt inter) {
#ifndef BCC_BLOCK_IGNORE
	asm cli;

	numOfEntry=newEntry;
	IVTEntry::ivtSave=this;
	kv=0;



	oldRoutine=getvect(newEntry);
	setvect(numOfEntry, inter);
	asm sti;
#endif

}

void IVTEntry::signal() {
#ifndef BCC_BLOCK_IGNORE
	asm cli;

	if(kv!=0) {
			kv->signal();
#endif
	}
}

void IVTEntry::callOldFun(){
#ifndef BCC_BLOCK_IGNORE
	asm cli;
#endif
	(*oldRoutine)();
#ifndef BCC_BLOCK_IGNORE
	asm sti;
#endif
}

IVTEntry::~IVTEntry() {
#ifndef BCC_BLOCK_IGNORE
	asm cli
	setvect(numOfEntry, oldRoutine);
	(*oldRoutine)();
	outportb(0x60, 0);
	asm sti
#endif
}

