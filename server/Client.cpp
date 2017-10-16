#include "Client.hpp"
#include <unistd.h>

Client::Client() : file_(""), ready_(false) , offset_(0)
{

}

Client::~Client()
{
	close(ofd_);
}

void Client::set_file(std::string file)
{
	file_ = file;
}

std::string Client::get_file()
{
	return file_;
}


bool Client::is_ready()
{
	return ready_;
}

void Client::done()
{
	ready_ = true;
	return;
}

void Client::set_ofd(int n)
{
	ofd_ = n;
}

int Client::get_ofd()
{
	return ofd_;
}

void Client::set_f_size(long size)
{
	f_size_ = size;
}

long int Client::get_f_size()
{
	return f_size_;
}

 void Client::set_offset(off_t offset)
{
	offset_ = offset;
}

off_t Client::get_offset()
{
	return offset_;
}

