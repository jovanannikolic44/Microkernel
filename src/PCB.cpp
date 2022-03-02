/*
 * Pcb.cpp
 *
 *  Created on: Mar 26, 2020
 *      Author: OS1
 */

#include "PCB.h"
#include "ListPCB.h"
#include "Context.h"
#include "SCHEDULE.H"
#include "KernSem.h"
#include "ListSem.h"

int PCB::Id = 2;
volatile PCB* PCB::running = 0;

ListPCB* PCB::headP = new ListPCB();


PCB::PCB() {
	Context::lockFlag = 0;
	id = 0;
	stack = 0;
	ss = 0;
	sp = 0;
	bp = 0;
	t = 0;
	timeSlice = 4;
	waitMax=0;
	pocMax=0;
	stanje = ready;
	wtc=new ListPCB();
	PCB::running=this;
	// main u listu svih PCB-ova
	PCB::headP->addPCB(this);
	Context::lockFlag = 1;
	if(Context::wantChange)
		dispatch();
}
PCB::PCB(unsigned long size, unsigned int time) {
	stack = new unsigned [size];

	ss = 0;
	sp = 0;

	if(stack == 0) {
		cout<<"PCB stack is null";
		return;
	}
	id = Id++;

#ifndef BCC_BLOCK_IGNORE
	stack[size - 1] = 0x200;
	stack[size - 2] = FP_SEG(&PCB::wrapper);
	stack[size - 3] = FP_OFF(&PCB::wrapper);

	ss = FP_SEG(stack + size - 12);
	sp = FP_OFF(stack + size - 12);
#endif
	bp = sp;
	stanje = created;
	timeSlice = time;
	waitMax=0;
	pocMax=0;
	wtc = new ListPCB();
	t=0;
}

PCB::PCB(unsigned long size, unsigned int time, int type) {
		Context::lockFlag = 0;
		stack = new unsigned [size];
		ss = 0;
		sp = 0;

		if(stack == 0) {
			cout<<"idle stack";
			return;
		}
		id = 1;

	#ifndef BCC_BLOCK_IGNORE
		stack[size - 1] = 0x200;
		stack[size - 2] = FP_SEG(&PCB::idleFunction);
		stack[size - 3] = FP_OFF(&PCB::idleFunction);
		ss = FP_SEG(stack + size - 12);
		sp = FP_OFF(stack + size - 12);
	#endif
		bp = sp;
		stanje = thIdle;
		timeSlice = time;
		waitMax=0;
		pocMax=0;
		wtc = 0;
		t=0;
		Context::lockFlag = 1;
		if(Context::wantChange)
			dispatch();
	}

void PCB::idleFunction() {
	while(1) {
		for(int i=0; i<1000; i++)
			for(int j = 0; j<1000; j++);
		dispatch();
	}
}


PCB::~PCB() {
	if(PCB::headP!=0) {
		PCB::headP->removePCBid(this->id);
	}


	if(stack!=0) {
		delete stack;
	}

	if(wtc!=0)
		delete wtc;
}


void PCB::wrapper() {
	if(PCB::running != 0) {
		PCB::running->t->run();

		Context::lockFlag = 0;

		PCB* k = 0;
		if(PCB::running->wtc!=0){

		int pocetnaDuzinaListe = PCB::running->wtc->duz;

		for(int i = 0; i<pocetnaDuzinaListe; i++) {

			k=PCB::running->wtc->removePCB();
			if(k!=0){
				k->stanje = ready;
				Scheduler::put(k);
			}
			else {
				cout<<"wrapper k je null";
			}
		}

		PCB::running->stanje = terminated;

		}

		Context::lockFlag = 1;
		dispatch();
	}
}


int PCB::getID() {
	return id;
}



