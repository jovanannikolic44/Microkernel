/*
 * ListPCB.h
 *
 *  Created on: Mar 27, 2020
 *      Author: OS1
 */

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
	void addPCB(PCB* pc);			// dodaje na kraj
	PCB* removePCB();				// uzima sa pocetka
	PCB* removePCBid(int identif);	// uklanja na osnovu id-ja
	PCB* getPCBbyIndex(int index);
	PCB* getPCBid(int identif);
	int checkPCB(int value);
	~ListPCB();
	void ispisiListu();
};

#endif /* LISTPCB_H_ */
