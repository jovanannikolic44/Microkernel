/*
 * ListPCB.cpp
 *
 *  Created on: Mar 27, 2020
 *      Author: OS1
 */

#include "ListPCB.h"
#include "Context.h"
#include "SCHEDULE.H"


ListPCB::ListPCB() {
	prvi = 0;
	posl = 0;
	duz = 0;
}

void ListPCB::addPCB(PCB* pc) {

	Elem* novi = new Elem(pc);
	if(prvi == 0) {
		prvi = novi;
	}
	else
		posl->sled = novi;
	posl = novi;

	duz = duz + 1;
}

PCB* ListPCB::removePCB() {
	if(prvi != 0) {
		Elem* p = prvi;
		if(prvi == posl) {
			prvi = 0;
			posl = 0;
		}
		else {
			prvi = prvi->sled;
			p->sled = 0;
		if(prvi == 0)
			posl = 0;
		}
		duz--;
		PCB* temp=p->pcb;
		delete p;
		return temp;
	}
	return 0;
}

PCB* ListPCB::getPCBbyIndex(int index) {
	Elem* tek=prvi;
	for(int i=0; i<duz; i++) {
		if(i==index) {
			break;
		}
		tek=tek->sled;

	}
	return tek->pcb;
}


PCB* ListPCB::removePCBid(int identif) {
	if(prvi == 0)
		return 0;
	Elem* tek = 0;
	Elem* pret = 0;
	for(tek = prvi; tek!=0;) {
		if(tek->pcb->getID() == identif) {
			if(prvi == posl) {
				prvi = 0;
				posl = 0;
				duz--;
				break;
			}
			else if(prvi == tek) {
				prvi = tek->sled;
				tek->sled = 0;
				duz--;
				break;
			}
			else if(posl == tek) {
				posl = pret;
				pret->sled = 0;
				duz--;
				break;
			}
			else {
				pret->sled = tek->sled;
				tek->sled = 0;
				duz--;
				break;
			}
		}
		else {
			pret = tek;
			tek = tek->sled;
		}
	}
	PCB* temp=tek->pcb;
	delete tek;
	return temp;
}

PCB* ListPCB::getPCBid(int identif) {
	if(prvi == 0)
		return 0;			// ako ne postoji ni jedan element u listi vrati 0

	Elem* tek = 0;
	for(tek = prvi; tek!=0; tek=tek->sled) {
		if(tek->pcb->getID() == identif) {
			break;
		}
	}
	if(tek!=0)
		return tek->pcb;
	else
		return 0;
}

int ListPCB::checkPCB(int value) {
	PCB* p=0;

	if(prvi == 0){
		return value;
	}

	Elem* tek=prvi;
	Elem* sled=tek->sled;
	while(tek!=0) {
		if(tek->pcb->waitMax > 0) {
			tek->pcb->waitMax--;
			if(tek->pcb->waitMax<=0) {

				p=removePCBid(tek->pcb->id);
				if(p!=0){
					p->stanje=ready;
					value=value+1;
					Scheduler::put(p);
				}
			}
		}
		tek = sled;
		// ako je jedan element u listi i radim onda ce sled biti null, pa ne smem da radim sled->sled
		if(sled!=0)
			sled = sled->sled;
	}
	return value;
}


ListPCB::~ListPCB() {
	Elem* stari;
		while(prvi) {
			stari = prvi;
			prvi = prvi->sled;
			delete stari;
		}
		prvi = 0;
		posl = 0;
		duz = 0;
}

void ListPCB::ispisiListu() {
	for(Elem* tek=prvi; tek!=0; tek=tek->sled) {
		cout<<tek->pcb->id;
	}
}


