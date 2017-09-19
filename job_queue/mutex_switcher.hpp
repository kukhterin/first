#ifndef _MUTEX_LOCK_
#define _MUTEX_LOCK_
#include <pthread.h>

void mutex_lock(pthread_mutex_t*);
int mutex_trylock(pthread_mutex_t*);
void mutex_unlock(pthread_mutex_t*);
	
#endif
