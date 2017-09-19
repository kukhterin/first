#include "Queue.hpp"
#include <iostream>
#include <pthread.h>
#include <time.h>

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
	std::string result = j_queue_.front();
	j_queue_.pop();
	return result;
}
		
void Queue::put(std::string s)
{
	j_queue_.push(s);
}

bool Queue::is_empty()
{
	return j_queue_.empty();
}

