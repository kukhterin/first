#include "Queue.hpp"
#include <iostream>
#include <pthread.h>
#include <cstdlib>
#include <dirent.h>// for file listing from directory
#include "put_get_file.hpp"
#include "mutex_switcher.hpp"
#include "md5.hpp"

Queue::Queue()
{
	std::cout << "Insert path to your durectory: " << std::endl;
	std::cin >> path_;
	//path_ = "/home/kukhterin/projects/JobQueue/New";
	
	mydir_ = opendir((path_).c_str()); 
    if(mydir_ == NULL) 
	{
        std::cout << "Opendir Error";
		exit(-1);
	}
	pthread_mutex_init(&mtx_, NULL);
	pthread_cond_init(&cond_, NULL);
}

Queue::~Queue()
{
	closedir(mydir_);
	pthread_mutex_destroy(&mtx_);
	pthread_cond_destroy(&cond_);
}

void Queue::get()
{
	int status = 0;
	while(true)
	{
		if(mutex_trylock(&mtx_))
			continue;
		while((j_queue_.empty()))
			pthread_cond_wait(&cond_, &mtx_);
		std::string file = get_file(&j_queue_);
		mutex_unlock(&mtx_);
		std::cout << "MD5 sum of " << file << ": " << md5_hash(file) << std::endl;			
	}
}
		
void Queue::put()
{
	while(entry_ = readdir(mydir_)) 
	{
		if(mutex_trylock(&mtx_))
			continue;
		put_file(&j_queue_, &path_, entry_);
		pthread_cond_signal(&cond_);
		mutex_unlock(&mtx_);
	}
	//pthread_exit(NULL);
}

