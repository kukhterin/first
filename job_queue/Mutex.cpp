#include "Mutex.hpp"
#include "ScopedLock.hpp"
#include <cstring>
#include <iostream>
#include <cerrno>

Mutex::Mutex()
{
	pthread_mutex_init(&mtx_, NULL);
}

Mutex::~Mutex()
{
	pthread_mutex_destroy(&mtx_);
}

void Mutex::lock()
{
	int status = pthread_mutex_lock(&mtx_);
	if(status != 0)
	{
		std::cout << strerror(status);
	}
}

void Mutex::unlock()
{
	int status = pthread_mutex_unlock(&mtx_);
		if(status != 0)
		{
			std::cout << strerror(status);
			return;
		}
}
