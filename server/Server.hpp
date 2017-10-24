#include <map>

#include <sys/epoll.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string>

#include "Client.hpp"
#include "Socket.hpp"

#ifndef _SERVER_
#define _SERVER_

typedef int flags;
typedef int connections;
typedef int file_descriptor;
typedef const char* port;

class Server
{
public:
	
	Server(flags, port, connections);
	~Server();
	
private:
	
	Server(const Server&);
	void operator=(const Server&);
	
	void start();
	void wait();
	void Send(const file_descriptor);
	
	char *ROOT_, c_;
	int efd_;
	int connections_;
	std::string port_;
	struct epoll_event event_;
	struct epoll_event* events_;
	std::map<int, Client> c_map_;
	Socket listenfd_;

};

#endif
