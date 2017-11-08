#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <errno.h>
#include <ios>
#include <string.h>
#include <stdlib.h>
#include "Timer.hpp"

//Timer t(__FUNCTION__);

Timer::Timer(std::string name) : name_(name)
{
	start_time_ =  std::clock();
	if(start_time_ == -1)
	{
		exit(-1);
	}
}

Timer::~Timer()
{
	std::ofstream fout;
	fout.open(FILE, std::ios_base::app);
	end_time_ =  std::clock();
	if(end_time_ == -1)
	{
		fout << strerror(errno) << std::endl;
		exit(-1);
	}
	search_time_ = end_time_ - start_time_;
	res_time_ = (double)search_time_/CLOCKS_PER_SEC;
	time_t cur_time;
	time(&cur_time);
	fout << "[" << strtok(ctime(&cur_time), "\n") << "] " << name_ << " runtime = " << res_time_ << std::endl;
	fout.close();
	
}
