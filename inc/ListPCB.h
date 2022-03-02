#ifndef LISTPCB_H_
#define LISTPCB_H_
#include "PCB.h"
#include "SCHEDULE.H"
class ListPCB {
	struct Elem {
		PCB* pcb;
		Elem* sled;
		Elem( PCB* pcbb, Elem* sledd = 0) : pcb(pcbb) {
			sled = sledd;
		}
	};
public:
	Elem* prvi;
	Elem* posl;
	int duz;

public:
	ListPCB();
	void addPCB(PCB* pc);			// add PCB to the end of the list
	PCB* removePCB();				// remove PCB from the beginning
	PCB* removePCBid(int identif);	
	PCB* getPCBbyIndex(int index);
	PCB* getPCBid(int identif);
	int checkPCB(int value);
	~ListPCB();
	void ispisiListu();
};

#endif /* LISTPCB_H_ */
