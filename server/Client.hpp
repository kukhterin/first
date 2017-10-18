#include <string>
#include <sys/types.h>

#ifndef _CLIENT_
#define _CLIENT_

class Client
{
private:
	void operator=(const Client&);
	std::string file_;
	long		f_size_;
	int 		offset_;
	bool		done_;
	int 		ofd_;
	int 		bytes_read_;
	int			buff_size_;
	
public:
	Client();
	~Client();
	bool 		set_file(std::string);
	std::string get_file();
	bool		is_ready();
	void 		set_buff_size(const int);
	void 		send(const int);
};

#endif
