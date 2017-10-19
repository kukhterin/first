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
{
	
}

Socket::~Socket()
{
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
	addrlen_ = sizeof clientaddr_;
	int new_fd = accept (fd_, (struct sockaddr *) &clientaddr_, &addrlen_);
	if (new_fd == -1)
	{
		if ((errno != EAGAIN) && (errno != EWOULDBLOCK))
			std::cout << "Accept error" << std::endl;
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
		perror ("getaddrinfo() error");
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
		fprintf(stderr, "Could not bind\n");
		exit(-1);
	}

	freeaddrinfo(res); 					//no longer needed
}

void Socket::sock_listen(int connections)
{
	if (listen (fd_, connections) == -1 )
	{
		perror("listen error");
		exit(-1);
	}
}

void Socket::make_non_blocking()
{
	int flags, s;
	
	flags = fcntl (fd_, F_GETFL, 0);
	if (flags == -1)
		{
		perror ("fcntl error");
		exit(-1);
		}

	flags |= O_NONBLOCK;
	s = fcntl (fd_, F_SETFL, flags);
	if (s == -1)
		{
			perror ("fcntl");
			exit(-1);
		}
}
