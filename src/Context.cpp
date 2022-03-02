/*
 * Context.cpp
 *
 *  Created on: Apr 9, 2020
 *      Author: OS1
 */

#include "Context.h"
#include "SCHEDULE.H"
#include "KernSem.h"
#include "ListSem.h"

Context::Context() {}

Context::~Context() {}

volatile int Context::counter = 4;
volatile unsigned int Context::lockFlag = 1;
volatile int Context::wantChange = 0;
volatile PCB* Context::pc=new PCB(4096, 2, 0);

volatile unsigned tsp;
volatile unsigned tss;
volatile unsigned tbp;

extern void tick();

void interrupt timer() {
#ifndef BCC_BLOCK_IGNORE
	if(!Context::wantChange	&& PCB::running->timeSlice!=0) {
		if(Context::counter > 0)
			Context::counter--;
	}

	if(KernelSem::allSems!=0) {
		if(!Context::wantChange) {
			tick();
			KernelSem::allSems->checkSem();
		}
	}

	if(Context::wantChange || (PCB::running->timeSlice !=0 && Context::counter==0)) {
		if(Context::lockFlag == 1) {

			// moram da radim promenu konteksta
			Context::wantChange = 0;

			// cuvam stari kontekst
			asm {
				mov tsp, sp
				mov tss, ss
				mov tbp, bp
			}
			PCB::running->sp = tsp;
			PCB::running->ss = tss;
			PCB::running->bp = tbp;

			// biram novi running

			if(PCB::running->stanje == ready) {
				Scheduler::put((PCB*)PCB::running);
			}

			PCB::running = Scheduler::get();

			if(PCB::running==0) {
				PCB::running=Context::pc;
			}

			// Restauracija konteksta

			tsp = PCB::running->sp;
			tss = PCB::running->ss;
			tbp = PCB::running->bp;

			Context::counter = PCB::running->timeSlice;

			asm {
				mov sp, tsp
				mov ss, tss
				mov bp, tbp
			}
		} else {
			Context::wantChange = 1;
		}
	}

	if(!Context::wantChange) asm int 60h;
}


unsigned oldTimerOFF, oldTimerSEG;

// postavljanje prekidne rutine (timer) na 8h, a stare prekidne rutine na 60h
void inic() {

	asm{
		cli
		push es
		push ax

		mov ax,0   //  ; inicijalizuje rutinu za tajmer
		mov es,ax

		mov ax, word ptr es:0022h //; pamti staru rutinu
		mov word ptr oldTimerSEG, ax
		mov ax, word ptr es:0020h
		mov word ptr oldTimerOFF, ax

		mov word ptr es:0022h, seg timer	 //postavlja
		mov word ptr es:0020h, offset timer //novu rutinu

		mov ax, oldTimerSEG	 //	postavlja staru rutinu
		mov word ptr es:0182h, ax //; na int 60h
		mov ax, oldTimerOFF
		mov word ptr es:0180h, ax

		pop ax
		pop es
		sti
	}

}

// vracanje stare prekidne rutine na 8h
void restore() {

	asm {
		cli
		push es
		push ax

		mov ax,0
		mov es,ax


		mov ax, word ptr oldTimerSEG
		mov word ptr es:0022h, ax
		mov ax, word ptr oldTimerOFF
		mov word ptr es:0020h, ax

		pop ax
		pop es
		sti

	}
	Context::wantChange = 0;
#endif
}
