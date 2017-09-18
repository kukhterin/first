#define _GLIBCXX_USE_CXX11_ABI 0
#include <iostream>
#include <pthread.h>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include "Queue.hpp"

// g++ -o md5  main.cpp md5.cpp mutex_switcher.cpp put_get_file.cpp Queue.cpp -pthread -lssl -lcrypto 
int main(int argc, char **argv) {
    
	pthread_t t0, t1, t2, t3; 
	size_t SIZE = 4;
	int status;
	Queue JQ;
	pthread_t threads[] = {t0, t1, t2, t3};
	
	for(size_t i = 1; i < SIZE; i++)
	{
		status = pthread_create (&threads[i], NULL, Queue::func<Queue, &Queue::get>, &JQ);
		if(status != 0)
		{
			std::cout << strerror(status);
			exit(1);
		}
	}

	status = pthread_create(&t0, NULL, Queue::func<Queue, &Queue::put>, &JQ);
	if(status != 0)
	{
		std::cout << strerror(status);
		exit(1);
	}
	
//////////////////////////////////////////////////////////////////////////////////
	
	for(size_t i = SIZE-1; i >= 0; i--)
	{
		status = pthread_join (threads[i], NULL);
		if(status != 0)
		{
			std::cout << strerror(status);
			exit(1);
		}	
	}
	JQ.~Queue();
	exit(EXIT_SUCCESS);
}