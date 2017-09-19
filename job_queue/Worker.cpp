#include <iostream>
#include "Worker.hpp"
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
		std::string result = (queue_->get());
		if(result == "")
			break;
		std::cout << "MD5 sum of " << result << ": " << md5_hash(result) << std::endl;
		continue;
	}
	pthread_exit(NULL);
	return;
}

