#include "put_get_file.hpp"

void put_file(std::queue<std::string>* q, std::string* path, struct dirent* entry)
{
	
	
	std::string tmp = (std::string)(entry->d_name);
	std::string s = *path + "/";
	if(tmp != "." && tmp != "..")
	{
		s += tmp;
		q->push(s);
	}	
	return;
}

std::string get_file(std::queue<std::string>* q)
{
	std::string file = "";
	file = q->front();
	q->pop();
	
	return file;
}