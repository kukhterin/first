#include <pthread.h>
#include <iostream>
#include <cstring>
#include "thread_func.hpp"
#ifndef _THREAD_
#define _THREAD_

template <class A, void(A::*F)()>
class Thread 
{
private:
	pthread_t thread_;
	void *(*start)(void *);
	void *arg_;
	const pthread_attr_t* attr_;

public:
	 Thread(const pthread_attr_t* attr, void* arg) : attr_(attr), arg_(arg)
	{
		int status = pthread_create(&thread_, attr_, thread_func<A, &A::run>, arg_); // thread_func<A, &A::F> /// error: ‘F’ is not a member of ‘Worker’

		if(status != 0)
		{
			std::cout << strerror(status);
			return;
		}
	}
	
	~Thread()
	{
	int status = pthread_join(thread_, NULL);
		if(status != 0)
		{
			std::cout << strerror(status);
			return;
		}	
	}	
};

#endif
