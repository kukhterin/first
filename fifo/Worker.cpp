#include <iostream>
#include <cstdio>
#include <string.h>

#include "Worker.hpp"

Worker::Worker(NamedPipe &p) : pipe_(p)
{
	run();
}

void Worker::run()
{
	std::string stop = "stop";
	std::string empty = "";
	while(true)
	{
		std::string result = (pipe_.answer());
		
		if(result == stop)
			break;

		if(result == empty)
			continue;
		else
		{
			std::cout << result << std::endl;
			continue;
		}
	}
	return;
}



