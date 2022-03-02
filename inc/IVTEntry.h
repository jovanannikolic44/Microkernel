/*
 * IVTEntry.h
 *
 *  Created on: May 23, 2020
 *      Author: OS1
 */

#ifndef IVTENTRY_H_
#define IVTENTRY_H_

typedef void interrupt (*pInterrupt) (...);

class IVTEntry {
public:
	friend class KernelEv;
	KernelEv* kv;
	int numOfEntry;
	pInterrupt oldRoutine;
	static IVTEntry* ivtSave;

public:
	IVTEntry(int newEntry, pInterrupt inter);
	void signal();
	void callOldFun();
	~IVTEntry();
};


#endif /* IVTENTRY_H_ */
