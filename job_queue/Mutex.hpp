#include <pthread.h>
#include "CondVar.hpp"
#ifndef _MUTEX_
#define _MUTEX_

class Mutex
{
friend class CondVar;
private:
	pthread_mutex_t mtx_;
	Mutex(const Mutex&);
	void operator=(const Mutex&);
public:
	Mutex();
	~Mutex();
	void lock();
	void unlock();

};
	
#endif
