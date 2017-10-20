#include "Socket.hpp"
#include <iostream>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <string.h>
#include <errno.h>

Socket::Socket()
{}

Socket::~Socket()
{
	
	std::cout << "SOCKET IS CLOSE" << std::endl;
	close(fd_);
}

void Socket::operator=(const Socket& socket)
{
	if(fd_ != socket.fd_)
		fd_ = socket.fd_;
	else
		std::cout << "Same socket!" << std::endl;
}

void Socket::operator=(const int& i)
{
	fd_ = i;
}

bool Socket::operator==(const Socket& sock)
{
	return fd_ == sock.fd_;
}

bool Socket::operator==(int i)
{
	return fd_ == i;
}


int Socket::sock_accept()
{
	addrlen_ = sizeof sockaddr_;
	int new_fd = accept (fd_, (struct sockaddr *) &sockaddr_, &addrlen_);
	if (new_fd == -1)
	{
		if ((errno != EAGAIN) && (errno != EWOULDBLOCK))
			s_err("Accept error");
	}

	return new_fd;
}

void Socket::create_and_bind(int flags, char* port)
{
	struct addrinfo hints, *res, *rp;
	// getaddrinfo for host
	memset (&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = flags;						//for wildcard IP address 
	if (getaddrinfo(NULL, port, &hints, &res) != 0)
	{
		s_err("getaddrinfo() error");
		exit(-1);
	}

	/* getaddrinfo() returns a list of address structures.
              Try each address until we successfully bind(2).
              If socket(2) (or bind(2)) fails, we (close the socket
              and) try the next address. */

	for (rp = res; rp != NULL; rp = rp->ai_next)
	{
		fd_ = socket (rp->ai_family, rp->ai_socktype, 0);
		if (fd_ == -1) 
			continue;
		
		if (bind(fd_, rp->ai_addr, rp->ai_addrlen) == 0) 
			break; //success
	}
	if (rp == NULL) 					//no address succeeded 
	{
		s_err("Could not bind");
		exit(-1);
	}

	freeaddrinfo(res); 					//no longer needed
}

void Socket::sock_listen(int connections)
{
	if (listen (fd_, connections) == -1 )
	{
		s_err("listen error");
		exit(-1);
	}
}

void Socket::make_non_blocking()
{
	int flags, s;
	
	flags = fcntl (fd_, F_GETFL, 0);
	if (flags == -1)
		{
		s_err("fcntl error");
		exit(-1);
		}

	flags |= O_NONBLOCK;
	s = fcntl (fd_, F_SETFL, flags);
	if (s == -1)
		{
			s_err("Fcntl");
			exit(-1);
		}
}


void Socket::s_err(std::string s)
{
	std::cout << s << ": " << strerror(errno) << std::endl;
}

/*
int Socket::accept()
{
	int		n;
again:
	if ( (n = accept(fd_, sockaddr_, addrlen_)) < 0) 
	{
#ifdef	EPROTO
		if (errno == EPROTO || errno == ECONNABORTED)
#else
		if (errno == ECONNABORTED)
#endif
			goto again;
		else
			s_err("Accept error");
	}
	return n;
}

void Socket:: bind()
{
	if (bind(fd_, sockaddr_, addrlen_) < 0)
		s_err("Bind error");
}

void Socket::connect()
{
	if (connect(fd_, sockaddr_, addrlen_) < 0)
		std::cout << "Connect error" << std::endl;
}

void Socket::listen(int backlog)
{

	if (listen(fd_, backlog) < 0)
		s_err("Listen error");
}
*/
