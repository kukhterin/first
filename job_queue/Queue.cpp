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
	ScopedLock sl(mtx_);
	while(j_queue_.empty())
	{
		if(closed_)
			return "";
		c_var_.wait(mtx_);
	}
	std::string result = j_queue_.front();
	j_queue_.pop();
	return result;
}
		
void Queue::put(std::string s)
{
	ScopedLock sl(mtx_);
	j_queue_.push(s);
	c_var_.signal();
}

void Queue::close_up()
{
	ScopedLock sl(mtx_);
	closed_ = true;
	c_var_.broadcast();
}
