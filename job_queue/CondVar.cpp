#include "CondVar.hpp"
#include <iostream>
#include <cstring>

CondVar::CondVar()
{
	pthread_cond_init(&cond_, NULL);
}

CondVar::~CondVar()
{
	pthread_cond_destroy(&cond_);
}

void CondVar::signal()
{
	int status_ = pthread_cond_signal(&cond_);
	if(status_ != 0)
	{
		std::cout << strerror(status_);
	}
}

void CondVar::broadcast()
{
	int status_ = pthread_cond_broadcast(&cond_);
	if(status_ != 0)
	{
		std::cout << strerror(status_);
	}
}

void CondVar::wait(Mutex &mutex)
{
	mutex.wait(cond_);
}
