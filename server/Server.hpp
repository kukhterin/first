#include <sys/socket.h>
#include<arpa/inet.h>

#ifndef _SERVER_
#define _SERVER_

#define CONNMAX 1000
#define BYTES 1024
#define PORT "8080" //standart http port

class Server
{
private:
	char *ROOT_, c_;
	int listenfd_, slot_, clients_[CONNMAX];
	struct sockaddr_in clientaddr_;
	socklen_t addrlen_;
	
public:
	Server();
	//~Server();
	void startServer();
	void respond(int);
};

#endif
