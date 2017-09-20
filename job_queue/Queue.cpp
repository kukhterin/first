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
	closed_ = false;
}

Queue::~Queue()
{
	pthread_mutex_destroy(&mtx_);
	pthread_cond_destroy(&cond_);
	
}

std::string Queue::get()
{	
	mutex_lock(&mtx_);
	
	while(j_queue_.empty())
	{
		if(closed_)
		{
			mutex_unlock(&mtx_);
			return "";
		}
		pthread_cond_wait(&cond_, &mtx_);
	}
	
	std::string result = j_queue_.front();
	j_queue_.pop();
	mutex_unlock(&mtx_);
	return result;
}
		
void Queue::put(std::string s)
{
	mutex_lock(&mtx_);
	j_queue_.push(s);
	int status_ = pthread_cond_signal(&cond_);
	if(status_ != 0)
	{
		std::cout << strerror(status_);
		mutex_unlock(&mtx_);
		return;
	}
	mutex_unlock(&mtx_);
}

void Queue::is_closed()
{
	closed_ = true;
	int status_ = pthread_cond_broadcast(&cond_);
	if(status_ != 0)
	{
		std::cout << strerror(status_);
		return;
	}
}
