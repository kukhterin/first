#include "ScopedLock.hpp"
#include <string.h>
#include <iostream>

ScopedLock::ScopedLock(pthread_mutex_t* mutex) : mtx_(mutex)
{
	int status = pthread_mutex_lock(mtx_);
	if(status != 0)
	{
		std::cout << strerror(status);
	}
}

ScopedLock::~ScopedLock()
{
	int status = pthread_mutex_unlock(mtx_);
		if(status != 0)
		{
			std::cout << strerror(status);
		}
}


