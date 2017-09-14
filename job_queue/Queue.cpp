#include "Queue.hpp"
#include <iostream>
#include <pthread.h>
#include <cstdlib>
#include <string.h>
#include <unistd.h>//sleep 
#include "md5.hpp"
#include <dirent.h>// for file listing from directory
#include <cerrno>


Queue::Queue()
{
	std::cout << "Insert path to your durectory: " << std::endl;
	std::cin >> path_;
	mydir_ = opendir((path_).c_str()); 
	//mydir_ = opendir("/home/kukhterin/projects/JobQueue/New"); 
    if(mydir_ == NULL) 
	{
        std::cout << "Opendir Error";
		exit(-1);
	}
	pthread_mutex_init(&mtx_, NULL);

}

void Queue::get()
{
	std::string file = "";
	while((j_queue_.empty()))
		usleep(1000);
	while(!(j_queue_.empty()))
	{
		int status = pthread_mutex_trylock(&mtx_);
		if(status == EBUSY)
		{
			usleep(1000);
			continue;
		}
		file = j_queue_.front();
		j_queue_.pop();
		status = pthread_mutex_unlock(&mtx_);
		if(status != 0)
		{
			std::cout << strerror(status);
			exit(1);
		}
		if(file != "")
			std::cout << "MD5 sum of " << file << ": " << md5_hash(file) << std::endl;
		usleep(1000);			
	}
	pthread_exit(NULL);
}

void Queue::put()
{
	while((entry_ = readdir(mydir_)) != NULL) 
	{
		int status = pthread_mutex_lock(&mtx_);
		if(status != 0)
		{
			std::cout << strerror(status);
			exit(1);
		}
		std::string tmp = (std::string)(entry_->d_name);
		std::string s = path_ + "/";
		//std::string s = "/home/kukhterin/projects/JobQueue/New/";
		if(tmp != "." && tmp != "..")
		{
			s += tmp;
			j_queue_.push(s);
			//std::cout << j_queue_.back() << std::endl;
			
		}
		//const char* ch = s.c_str(); 
		status = pthread_mutex_unlock(&mtx_);
		if(status != 0)
		{
			std::cout << strerror(status);
			exit(1);
		}
		usleep(1000);
	}
	closedir(mydir_);
	pthread_exit(NULL);
}
