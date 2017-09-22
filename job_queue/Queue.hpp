#include <queue>
#include <string>
#include <pthread.h>
#include "Mutex.hpp"
#include "CondVar.hpp"
#ifndef _QUEUE_
#define _QUEUE_

class Queue
{
private: 
	Queue(const Queue&);
	void operator=(const Queue&);
	std::queue<std::string> j_queue_;
	Mutex mtx_;
	CondVar c_var_;
	bool closed_;
	
public:
	Queue();
	void put(std::string);
	std::string get();
	void close_up();
};

#endif

