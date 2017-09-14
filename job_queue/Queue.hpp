#include <queue>
#include <dirent.h>// for file listing from directory
#include <string>
#include <pthread.h>
#ifndef _QUEUE_
#define _QUEUE_

class Queue
{
private: 
	std::queue<std::string> j_queue_;
	pthread_mutex_t mtx_;
	pthread_cond_t cond_ ;
	DIR* mydir_;
	struct dirent* entry_;
	std::string path_;
public:
	Queue();
	void put();
	void get();
	
	template <class A, void(A::*F)()>
	static void* func(void* p)
	{
		A* a = static_cast<A*>(p);
		(a->*F)();//a->*F() - totally mot working
		return 0;
		
	}
};

#endif

