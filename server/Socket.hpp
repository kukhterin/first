#include <sys/socket.h>
#ifndef _SOCKET_
#define _SOCKET_

class Socket 
{
private:
	Socket(const Socket&);
	int fd_;
	struct sockaddr clientaddr_;
	socklen_t addrlen_;
public:
	Socket();
	~Socket();
	void operator=(const Socket&);
	void operator=(const int&);
	bool operator==(const Socket&);
	bool operator==(int);
		 operator int(){return fd_;}
	void make_non_blocking();
	void sock_listen(int);
	void create_and_bind(int, char*);
	int sock_accept();
	
};

#endif
