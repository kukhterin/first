#include <iostream>
#include <cstring>
#include "Thread.hpp"

Thread::Thread(const pthread_attr_t* attr, void *(*func)(void *), void* arg) : attr_(attr), start(func), arg_(arg) 
{
	
	int status = pthread_create(&thread_, attr_, start, arg_);
	if(status != 0)
	{
		std::cout << strerror(status);
		return;
	}
}

Thread::~Thread()
{
	int status = pthread_join(thread_, NULL);
		if(status != 0)
		{
			std::cout << strerror(status);
			return;
		}	
}


