#include "Context.h"
#include "IVTEntry.h"
#include "KernSem.h"
#include "ListSem.h"
#include "ListPCB.h"

extern int userMain(int argc, char* argv[]);

int main(int argc,char* argv []) {
	char ** argVV= argv;
	inic();
	PCB* mainT = new PCB();

	userMain (argc, argVV);


	delete mainT;
	restore();

	delete Context::pc;
	PCB::running = 0;
	IVTEntry::ivtSave = 0;


	delete PCB::headP;

	delete KernelSem::allSems;

	return 0;
}


