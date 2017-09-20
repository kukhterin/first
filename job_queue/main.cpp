#include <iostream>
#include <pthread.h>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <string>
#include <dirent.h>
#include "Queue.hpp"
#include "mutex_switcher.hpp"
#include "Worker.hpp"
#include "thread_func.hpp"

// g++ -o result  main.cpp md5.cpp mutex_switcher.cpp Queue.cpp Worker.cpp  -pthread -lssl -lcrypto
// mipsel-linux-g++ -o result_box main.cpp md5.cpp mutex_switcher.cpp Queue.cpp Worker.cpp -I/home/kukhterin/projects/c5320-sdk/include/openssl/ -L/home/kukhterin/projects/c5320-sdk/lib/ -pthread -lssl -lcrypto
int main(int argc, char **argv) {
   
	std::string path;
	pthread_t t1, t2, t3; 
	size_t SIZE = 3;
	pthread_t threads[] = {t1, t2, t3};
	int status;
	DIR* mydir;
	struct dirent* entry;

	std::cout << "Insert path to your directory: " << std::endl;
	std::getline ( std::cin, path);
	mydir = opendir(path.c_str()); 
    if(mydir == NULL) 
	{
		std::cout << "Opendir Error";
		exit(-1);
	}	
			
	Queue JQ;
	Worker worker(JQ);
			
	for(size_t i = 0; i < SIZE; i++)
	{
		status = pthread_create (&threads[i], NULL, thread_func<Worker, &Worker::run>, &worker);
		if(status != 0)
		{
			std::cout << strerror(status);
			exit(1);
		}
	}

	while(entry = readdir(mydir))
	{
		std::string tmp = (std::string)(entry->d_name);
		if(tmp == "." || tmp == "..")
			continue;
		std::string result = path + "/";
		result += tmp;
		JQ.put(result);
	}
	JQ.close_up();
	
	for(size_t i = 0; i < SIZE; i++)
	{
		status = pthread_join(threads[i], NULL);
		if(status != 0)
		{
			std::cout << strerror(status);
			exit(1);
		}	
	}
	
	return 0;
}
