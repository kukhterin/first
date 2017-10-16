#include <string>
#include <sys/types.h>

#ifndef _CLIENT_
#define _CLIENT_

class Client
{
private:
	std::string file_;
	long		f_size_;
	off_t 		offset_;
	bool		ready_;
	int 		ofd_;
	
public:
	Client();
	~Client();
	void 		set_file(std::string);
	void	 	set_offset(off_t);
	std::string get_file();
	off_t 		get_offset();
	bool		is_ready();
	void		done();
	void 		set_ofd(int);
	int			get_ofd();
	void		set_f_size(long);
	long		get_f_size();
};

#endif
