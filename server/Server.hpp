#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/epoll.h>

#ifndef _SERVER_
#define _SERVER_

#define CONNMAX 10000
#define BYTES 1024
#define PORT "8080" //standart http port


class Server
{
private:
	char *ROOT_, c_;
	int listenfd_, efd_;
	struct epoll_event event_;
	struct epoll_event* events_;
	struct sockaddr clientaddr_;
	socklen_t addrlen_;
	 
	
public:
	Server();
	//~Server();
	void startServer();
	void respond(int);
	void make_non_blocking(int);
};

#endif
