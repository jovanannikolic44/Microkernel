#ifndef PCB_H_
#define PCB_H_
#include <dos.h>
#include "Thread.h"
#include <iostream.h>

class ListPCB;
class Thread;
enum Stanje {created, ready, blocked, terminated, thIdle};
class PCB {
public:
	unsigned *stack;
	unsigned ss;
	unsigned sp;
	unsigned bp;
	unsigned timeSlice;
	Stanje stanje;
	static int Id;
	int id;
	Thread* t;		
	static volatile PCB* running;
	static ListPCB* headP;
	ListPCB* wtc;
	 int waitMax;
	 int pocMax;

public:
	friend class Thread;
	PCB();
	PCB(unsigned long size, unsigned int time);
	PCB(unsigned long size, unsigned int time, int type);
	~PCB();
	static void wrapper();
	static PCB* brisiID(int idPCB);
	static void idleFunction();
	int getID();

};
#endif /* PCB_H_ */


