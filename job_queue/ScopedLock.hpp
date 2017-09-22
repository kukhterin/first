#include "Mutex.hpp"
#include <pthread.h>
#ifndef _SCOPED_LOCK_
#define _SCOPED_LOCK_

class ScopedLock
{
public:
	ScopedLock(Mutex&); 
	~ScopedLock();
 
private:
	Mutex &mtx_;
	ScopedLock(const ScopedLock&);
	void operator=(const ScopedLock&);
	
};

#endif

