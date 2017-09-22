#ifndef _MUTEX_
#define _MUTEX_
#include <pthread.h>

class Mutex
{
private:
	pthread_mutex_t mtx_;
	Mutex(const Mutex&);
	void operator=(const Mutex&);
public:
	Mutex();
	~Mutex();
	void lock();
	void unlock();
	void wait(pthread_cond_t&);

};
	
#endif
