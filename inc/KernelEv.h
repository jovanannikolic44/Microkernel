/*
 * KernelEv.h
 *
 *  Created on: May 23, 2020
 *      Author: OS1
 */

#ifndef KERNELEV_H_
#define KERNELEV_H_
#include "PCB.h"


class IVTEntry;

class KernelEv {
public:
	PCB* creator;
	int value;
	int blockedPCB;
	int entry;
	IVTEntry* ivtEntry;


public:
	KernelEv(unsigned char ivtNo);
	void wait();
	void signal();
	virtual ~KernelEv();
};

#endif /* KERNELEV_H_ */
