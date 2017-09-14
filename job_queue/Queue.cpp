#include "Queue.hpp"
#include <iostream>
#include <pthread.h>
#include <cstdlib>

#include <unistd.h>//sleep 
#include <dirent.h>// for file listing from directory
#include "put_get_file.hpp"
#include "mutex_switcher.hpp"
#include "md5.hpp"

Queue::Queue()
{
	//std::cout << "Insert path to your durectory: " << std::endl;
	//std::cin >> path_;
	path_ = "/home/kukhterin/projects/JobQueue/New";
	
	mydir_ = opendir((path_).c_str()); 
    if(mydir_ == NULL) 
	{
        std::cout << "Opendir Error";
		exit(-1);
	}
	pthread_mutex_init(&mtx_, NULL);

}

void Queue::get()
{
	while((j_queue_.empty()))
		usleep(1000);
	
	while(!(j_queue_.empty()))
	{
		if(mutex_trylock(&mtx_))
			continue;
		
		std::string file = get_file(&j_queue_);
		
		
		mutex_unlock(&mtx_);
		
		
		std::cout << "MD5 sum of " << file << ": " << md5_hash(file) << std::endl;
		usleep(1000);			
	}
	pthread_exit(NULL);
}

void Queue::put()
{
	while((entry_ = readdir(mydir_)) != NULL) 
	{
		mutex_lock(&mtx_);
		
		put_file(&j_queue_, &path_, entry_);
			
		mutex_unlock(&mtx_);
		
		usleep(1000);
	}
	closedir(mydir_);
	pthread_exit(NULL);
}