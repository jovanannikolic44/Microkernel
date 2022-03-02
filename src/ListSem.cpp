/*
 * ListSem.cpp
 *
 *  Created on: Apr 20, 2020
 *      Author: OS1
 */

#include "ListSem.h"
#include "Context.h"
#include "SCHEDULE.H"

ListSem::ListSem() {
	prvi=0;
	posl=0;
	duz=0;

}

void ListSem::addSem(KernelSem* ks) {
	Semaphor* novi = new Semaphor(ks);
	if(prvi==0)
		prvi=novi;
	else
		posl->sled=novi;
	posl=novi;
	duz++;
}

KernelSem* ListSem::removeSemId(int identif) {
	if(prvi == 0)
		return 0;
	Semaphor* tek = 0;
	Semaphor* pret = 0;
	for(tek = prvi; tek!=0;) {
		if(tek->sem->id == identif) {
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

	KernelSem* temp=tek->sem;
	delete tek;
	return temp;
}

void ListSem::checkSem() {
	ListPCB* lp=0;
	for(Semaphor* t=prvi; t!=0; t=t->sled) {
			lp=t->sem->blockedList;
			t->sem->value=lp->checkPCB(t->sem->value);
	}
}

ListSem::~ListSem() {
	Semaphor* stari;
		while(prvi) {
			stari=prvi;
			prvi=prvi->sled;
			delete stari;
		}
		prvi=0;
		posl=0;
		duz=0;
}



