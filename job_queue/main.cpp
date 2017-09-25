#include <iostream>
#include <pthread.h>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <string>
#include <dirent.h>
#include "Queue.hpp"
#include "Worker.hpp"
#include "thread_func.hpp"
#include "Thread.hpp"

// g++ -o result  main.cpp md5.cpp mutex_switcher.cpp Queue.cpp Worker.cpp  -pthread -lssl -lcrypto
// mipsel-linux-g++ -o result_box main.cpp md5.cpp mutex_switcher.cpp Queue.cpp Worker.cpp -I/home/kukhterin/projects/c5320-sdk/include/openssl/ -L/home/kukhterin/projects/c5320-sdk/lib/ -pthread -lssl -lcrypto
int main(int argc, char **argv) {
   
	std::string path;
	int status;
	DIR* mydir;
	struct dirent* entry;

	//path = "/home/kukhterin/projects/JobQueue/New";
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
	
	Thread<Worker, &Worker::run> t1(NULL, &worker);	
	Thread<Worker, &Worker::run> t2(NULL, &worker);	
	Thread<Worker, &Worker::run> t3(NULL, &worker);	

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
	
	return 0;
}
