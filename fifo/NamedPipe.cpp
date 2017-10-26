#include <iostream>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
//#include <stdlib.h>
#include <algorithm>

#include "NamedPipe.hpp"
 
NamedPipe::NamedPipe()
{
	create();
}

NamedPipe::~NamedPipe()
{
	remove(NAMEDPIPE_NAME);
	close(fd_);
}

void NamedPipe::create()
{
	if ( mkfifo(NAMEDPIPE_NAME, RIGHTS) )
	{
        std::cout << "mkfifo error: " << strerror(errno) << std::endl;
        exit(-1);
    }
    std::cout << NAMEDPIPE_NAME << "is created" << std::endl;

    if ( (fd_ = open(NAMEDPIPE_NAME, O_RDONLY)) <= 0 ) 
	{
        std::cout << "open error: " << strerror(errno);
        exit(-1);
    }
}

std::string NamedPipe::answer()
{
	memset(buf_, '\0', BUFSIZE);

	if ( (len_ = read(fd_, buf_, BUFSIZE-1)) <= 0 ) 
	{
		return "";
	}
	std::string result = buf_;
	int size = len_/sizeof(char) - 1;
	result.resize(size);
	
	return result;
}

