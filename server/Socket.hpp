#include <string>

#include <sys/socket.h>

#ifndef _SOCKET_
#define _SOCKET_

typedef int flags;
typedef int connections;
typedef int file_descriptor;
typedef const char* port;
typedef std::string error;

class Socket 
{
public:
	
	Socket(const flags, const port, const connections);
	~Socket();
	Socket(const Socket&);
	void operator=(const Socket&);
	
	void Listen(const file_descriptor) const;
	int Accept();
	int get_fd();
	
private:
	
	int fd_;
	struct sockaddr sockaddr_;
	socklen_t addrlen_;
		
	void create_and_bind(const flags, const port);
	void make_non_blocking();
	void s_err(error);

	
};

#endif

