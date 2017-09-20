#include <cstdio>
#include "Worker.hpp"
#include "md5.hpp"


Worker::Worker(Queue &q) : queue_(q)
{}

void Worker::run()
{
	while(true)
	{
		std::string result = (queue_.get());
		if(result == "")
			break;
		std::printf("MD5 sum of %s: %s\n", result.c_str(), (md5_hash(result)).c_str());
		continue;
	}
	return;
}

