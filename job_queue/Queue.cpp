#include <iostream>
#include <pthread.h>
#include <time.h>
#include <string.h>
#include "Queue.hpp"
#include "ScopedLock.hpp"

Queue::Queue()
{
	closed_ = false;
}

std::string Queue::get()
{	
	ScopedLock sl(mtx_.get_m());
	while(j_queue_.empty())
	{
		if(closed_)
			return "";
		
		int status = pthread_cond_wait(c_var_.get_c(), mtx_.get_m());
		if(status != 0)
		{
			std::cout << strerror(status);
		}
	}
	std::string result = j_queue_.front();
	j_queue_.pop();
	return result;
}
		
void Queue::put(std::string s)
{
	ScopedLock sl(mtx_.get_m());
	j_queue_.push(s);
	c_var_.signal();
}

void Queue::close_up()
{
	ScopedLock sl(mtx_.get_m());
	closed_ = true;
	c_var_.broadcast();
}
