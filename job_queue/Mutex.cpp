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

pthread_mutex_t* Mutex::get_m()
{
	return &mtx_;
}


