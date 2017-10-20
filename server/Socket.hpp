#include <sys/socket.h>
#include <string>
#ifndef _SOCKET_
#define _SOCKET_

void make_non_blocking(int);

class Socket 
{
private:
	Socket(const Socket&);
	int fd_;
	struct sockaddr sockaddr_;
	socklen_t addrlen_;
public:
	Socket();
	Socket(int);
	~Socket();
	void s_err(std::string);
	void operator=(const Socket&);
	void operator=(const int&);
	bool operator==(const Socket&);
	bool operator==(int);
		 operator int(){return fd_;}
	void sock_listen(int);
	void create_and_bind(int, char*);
	int sock_accept();
	void make_non_blocking();
	
};

#endif
