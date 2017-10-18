#include "Client.hpp"
#include <unistd.h>
#include <sys/socket.h>
#include <iostream>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <cstdlib>
#include <fcntl.h>

Client::Client() : file_(""), done_(false), offset_(0)
{}

Client::~Client()
{
	close(ofd_);
}

void Client::send(const int fd)
{	
	set_buff_size(fd);
	char	data_to_send[buff_size_];
		
	bytes_read_ = pread(ofd_, data_to_send, buff_size_, offset_);
	if(bytes_read_ < 0)
	{
		std::cout << "pread: " << strerror(errno) << std::endl;
		exit(-1);
	}
	
	offset_ += bytes_read_;
	
	if( (write (fd, data_to_send, bytes_read_)) < 0)
	{
		std::cout << "write: " << strerror(errno) << std::endl;
		exit(-1);
	}
	
	if(offset_ == f_size_)
		done_ = true;	
	
}

void Client::set_buff_size(const int fd)
{
	int b_size = 0;
	int optlen = sizeof(b_size);
	if( (getsockopt(fd, SOL_SOCKET, SO_RCVBUF, &b_size, (socklen_t*)&optlen)) < 0)
	{
		std::cout << "getsockopt: " << strerror(errno) << std::endl;
		exit(-1);
	}
	buff_size_ = b_size;
}

bool Client::set_file(std::string file)
{
	file_ = file;
	struct stat file_stat;
	stat(file_.c_str(), &file_stat);
	f_size_ = file_stat.st_size;
	if ((ofd_ = open(file_.c_str(), O_RDONLY)) == -1 )
		return false;
	return true;
		
}

std::string Client::get_file()
{
	return file_;
}


bool Client::is_ready()
{
	return done_;
}
