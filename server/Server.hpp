#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <map>
#include "Client.hpp"
#include "Socket.hpp"

#ifndef _SERVER_
#define _SERVER_

#define CONNMAX 1024
#define PORT "80" //standart http port


class Server
{
private:
	Server(const Server&);
	void operator=(const Server&);
	char *ROOT_, c_;
	Socket listenfd_;
	int efd_;
	struct epoll_event event_;
	struct epoll_event* events_;
	std::map<int, Client> c_map_;
	 
	
public:
	Server();
	~Server();
	void startServer();
	void respond(int);
	void get();
	ssize_t writen(int, const void *, size_t);
	ssize_t read_n(int, void *, size_t);
};

#endif
