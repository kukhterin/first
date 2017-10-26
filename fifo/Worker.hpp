#include "NamedPipe.hpp"
#ifndef _WORKER_
#define _WORKER_

class Worker
{
private: 
	Worker(const Worker&);
	void operator=(const Worker&);
	NamedPipe &pipe_;
	
public:
	Worker(NamedPipe&);
	void run();
		
};

#endif
