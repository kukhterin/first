#include <string>

#include <sys/types.h>

#ifndef _CLIENT_
#define _CLIENT_

typedef int file_descriptor;
typedef std::string file_name;

class Client
{
public:
	
	Client();
	~Client();
	
	bool 		set_sending_file(const file_name);
	file_name	get_file();
	bool		is_ready();
	void 		send(const file_descriptor);
	
private:
	
	void operator=(const Client&);
	std::string	file_;
	int 		ofd_;
	long		f_size_;
	int 		offset_;
	bool		done_;
	int 		bytes_read_;
	int			buff_size_;
	void 		set_buff_size(const file_descriptor);

};

#endif
