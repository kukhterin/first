#include <queue>
#include <string>
#include <pthread.h>
#ifndef _QUEUE_
#define _QUEUE_

class Queue
{
private: 
	Queue(const Queue&);
	void operator=(const Queue&);
	std::queue<std::string> j_queue_;
	pthread_mutex_t mtx_;
	pthread_cond_t cond_;
	bool closed_;
	
public:
	Queue();
	~Queue();
	void put(std::string);
	std::string get();
	void is_closed();
};

#endif

