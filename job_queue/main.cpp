#define _GLIBCXX_USE_CXX11_ABI 0
#include <iostream>
#include <pthread.h>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include "Queue.hpp"



int main(int argc, char **argv) {
    
	pthread_t t0, t1, t2, t3; 
	int status;
	
	Queue JQ;

	status = pthread_create(&t1, NULL, Queue::func<Queue, &Queue::get>, &JQ);
	if(status != 0)
	{
		std::cout << strerror(status);
		exit(1);
	}
	
	status = pthread_create(&t2, NULL, Queue::func<Queue, &Queue::get>, &JQ);
	if(status != 0)
	{
		std::cout << strerror(status);
		exit(1);
	}
	
	status = pthread_create(&t3, NULL, Queue::func<Queue, &Queue::get>, &JQ);
	if(status != 0)
	{
		std::cout << strerror(status);
		exit(1);
	}
	
	status = pthread_create(&t0, NULL, Queue::func<Queue, &Queue::put>, &JQ);
	if(status != 0)
	{
		std::cout << strerror(status);
		exit(1);
	}
	
//////////////////////////////////////////////////////////////////////////////////
	
	status = pthread_join(t3, NULL);
	if(status != 0)
	{
		std::cout << strerror(status);
		exit(1);
	}	
	
	status = pthread_join(t2, NULL);
	{
		std::cout << strerror(status);
		exit(1);
	}
	
	status = pthread_join(t1, NULL);
	if(status != 0)
	{
		std::cout << strerror(status);
		exit(1);
	}
	
	status = pthread_join(t0, NULL);
	if(status != 0)
	{
		std::cout << strerror(status);
		exit(1);
	}
	
	
   exit(EXIT_SUCCESS);
}

