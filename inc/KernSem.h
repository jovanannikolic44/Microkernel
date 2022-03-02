/*
 * KernSem.h
 *
 *  Created on: Apr 20, 2020
 *      Author: OS1
 */

#ifndef KERNSEM_H_
#define KERNSEM_H_
#include "ListPCB.h"

class ListSem;
class KernelSem {
public:
	int value;
	static int Id;
	int id;
	ListPCB* blockedList;
	static ListSem* allSems;

public:
	KernelSem(int init=1);
	int waitSem(unsigned int maxTimeToWait);
	int signalSem(int n);
	void helper();
	virtual ~KernelSem();
};

#endif /* KERNSEM_H_ */
