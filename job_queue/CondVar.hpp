#ifndef _CONDVAR_
#define _CONDVAR_
#include <pthread.h>

class CondVar
{
private:
	pthread_cond_t cond_;
	CondVar(const CondVar&);
	void operator=(const CondVar&);
public:
	CondVar();
	~CondVar();
	void signal();
	void broadcast();
	pthread_cond_t* get_c();
};
	
#endif