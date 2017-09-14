#ifndef _PUT_FILE_
#define _PUT_FILE_
#include <queue>
#include <string>
#include <dirent.h>// for file listing from directory
#include <iostream>

void put_file(std::queue<std::string>*, std::string*, struct dirent*);

std::string get_file(std::queue<std::string>*);
	
#endif
