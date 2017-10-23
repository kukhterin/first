#include <string>

#include <sys/socket.h>

#ifndef _SOCKET_
#define _SOCKET_

void make_non_blocking(int);

class Socket 
{
public:
	
	Socket();
	~Socket();
	
	void operator=(const Socket&);
	void operator=(const int&);
	bool operator==(const Socket&);
	bool operator==(int);
		 operator int(){return fd_;}
	void s_err(std::string);
	void sock_listen(int);
	void create_and_bind(int, char*);
	int sock_accept();
	void make_non_blocking();
	
private:
	
	Socket(const Socket&);
	
	int fd_;
	struct sockaddr sockaddr_;
	socklen_t addrlen_;
	
};

#endif

