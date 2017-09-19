#include "Worker.hpp"
#include "mutex_switcher.hpp"
#include "md5.hpp"


Worker::Worker(Queue* q) 
{
	queue_ = q;
}

Worker::~Worker()
{
	
}


void Worker::run()
{
	int status = 0;
	while(true)
	{
		if(mutex_trylock(&(queue_->mtx_)))
			continue;
		if(queue_->is_empty())
		{
			if(!(timedwait(&(queue_->cond_), &(queue_->mtx_), 1)))
				break;
		}
	std::string result = (queue_->get());
	mutex_unlock(&(queue_->mtx_));
	std::cout << "MD5 sum of " << result << ": " << md5_hash(result) << std::endl;
	continue;
	}
	pthread_exit(NULL);
	return;
}

