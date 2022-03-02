#ifndef LISTSEM_H_
#define LISTSEM_H_
#include "KernSem.h"

class ListSem {
	struct Semaphor {
		KernelSem* sem;
		Semaphor* sled;
		Semaphor(KernelSem* ksem, Semaphor* sledd=0):sem(ksem) {
			sled=sledd;
		}
	};
public:
Semaphor* prvi;
Semaphor* posl;
int duz;

public:
	ListSem();
	void addSem(KernelSem* ks);
	KernelSem* removeSemId(int identif);
	void checkSem();
	~ListSem();
};

#endif  /* LISTSEM_H_ */
