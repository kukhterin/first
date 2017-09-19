#include "mutex_switcher.hpp"
#include <unistd.h>//sleep
#include <cstdlib>
#include <cstring>
#include <cerrno>
#include <time.h>  
#include <sys/time.h>



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

bool timedwait(pthread_cond_t* cond, pthread_mutex_t* mutex,  int sec_to_wait)
{
	int status = 0;
	struct timespec   ts;
	struct timeval    tp;
	status =  gettimeofday(&tp, NULL);
	ts.tv_sec  = tp.tv_sec;
    ts.tv_nsec = tp.tv_usec * 1000;
    ts.tv_sec += sec_to_wait;
	
	status = pthread_cond_timedwait(cond, mutex, &ts);
	if (status == ETIMEDOUT) 
	{
		status = pthread_mutex_unlock(mutex);
		if(status != 0)
		{
			std::cout << strerror(status);
			exit(1);
		}
		return false;
	}
	return true;
}









