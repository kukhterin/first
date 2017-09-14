#include "mutex_switcher.hpp"
#include <unistd.h>//sleep
#include <cstdlib>
#include <cstring>
#include <cerrno>



void mutex_lock(pthread_mutex_t* mtx)
{
	int status = pthread_mutex_lock(mtx);
	if(status != 0)
	{
		std::cout << strerror(status);
		exit(1);
	}
}

int mutex_trylock(pthread_mutex_t* mtx)
{
	int status = pthread_mutex_trylock(mtx);
		if(status == EBUSY)
		{
			usleep(1000);
			return 1;
		}
	return 0;
}

void mutex_unlock(pthread_mutex_t* mtx)
{
	int status = pthread_mutex_unlock(mtx);
		if(status != 0)
		{
			std::cout << strerror(status);
			exit(1);
		}
}









