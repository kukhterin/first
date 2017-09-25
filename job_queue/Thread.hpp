#include <pthread.h>
#ifndef _THREAD_
#define _THREAD_

class Thread 
{
private:
	pthread_t thread_;
	void *(*start)(void *);
	void *arg_;
	const pthread_attr_t* attr_;

public:
	Thread(const pthread_attr_t*, void *(*)(void *), void *);
	~Thread();
	

	
};

#endif
