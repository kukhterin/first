#include <iostream>
#include <pthread.h>
#include <time.h>
#include <string.h>
#include "Queue.hpp"
#include "mutex_switcher.hpp"


Queue::Queue()
{
	
	pthread_mutex_init(&mtx_, NULL);
	pthread_cond_init(&cond_, NULL);
}

Queue::~Queue()
{
	pthread_mutex_destroy(&mtx_);
	pthread_cond_destroy(&cond_);
	std::cout << "exit" << std::endl;
}

std::string Queue::get()
{	
	if(!(timedwait(&cond_, &mtx_, 1)))
		return "";
	std::string result = j_queue_.front();
	j_queue_.pop();
	return result;
}
		
void Queue::put(std::string s)
{
	mutex_lock(&mtx_);
	j_queue_.push(s);
	status_ = pthread_cond_signal(&cond_);
	if(status_ != 0)
	{
		std::cout << strerror(status_);
		return;
	}
	mutex_unlock(&mtx_);
}
