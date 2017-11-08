#include <ctime>
#include <bits/time.h> //clocks per second
#include <string>

#ifndef _TIMER_
#define _TIMER_

#define FILE "timer_log.txt"


class Timer
{
public:
	Timer(std::string);
	~Timer();
	
private:
	clock_t start_time_;
	clock_t end_time_;
	clock_t search_time_;
	double res_time_;
	std::string name_;
	
};

#endif
