#include "ScopedLock.hpp"
#include <string.h>
#include <iostream>

ScopedLock::ScopedLock(Mutex &mutex) : mtx_(mutex)
{
	mtx_.lock();
}

ScopedLock::~ScopedLock()
{
	mtx_.unlock();
}
