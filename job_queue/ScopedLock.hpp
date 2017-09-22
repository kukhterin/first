#ifndef _SCOPED_LOCK_
#define _SCOPED_LOCK_
#include <pthread.h>

class ScopedLock
{
public:
	ScopedLock(pthread_mutex_t*); 
	~ScopedLock();
 
private:
	pthread_mutex_t* mtx_;
	ScopedLock(const ScopedLock&);
	void operator=(const ScopedLock&);
	
};

#endif
