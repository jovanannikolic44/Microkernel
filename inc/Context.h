/*
 * Context.h
 *
 *  Created on: Apr 9, 2020
 *      Author: OS1
 */

#ifndef CONTEXT_H_
#define CONTEXT_H_
#include "PCB.h"

class Context {
public:
	static volatile int counter;
	static volatile unsigned int lockFlag;
	static volatile int wantChange;
	static volatile PCB* pc;

	Context();
	virtual ~Context();
};

void inic();
void interrupt timer();
void restore();

#endif /* CONTEXT_H_ */
