#include "Queue.hpp"
#ifndef _WORKER_
#define _WORKER_

class Worker
{
private: 
	Worker(const Worker&);
	void operator=(const Worker&);
	Queue &queue_;
	
public:
	
	Worker(Queue&);
	void run();
		
};

#endif
