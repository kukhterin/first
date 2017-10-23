#include <map>

#include <sys/epoll.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "Client.hpp"
#include "Socket.hpp"

#ifndef _SERVER_
#define _SERVER_

#define CONNMAX 1024
#define PORT "80" //standart http port


class Server
{
public:
	
	Server();
	~Server();
	
	void start_server();
	void respond(int);
	void server_wait();
	
private:
	
	Server(const Server&);
	
	void operator=(const Server&);
	char *ROOT_, c_;
	int efd_;
	
	struct epoll_event event_;
	struct epoll_event* events_;
	std::map<int, Client> c_map_;
	Socket listenfd_;

};

#endif
