#include "Server.hpp"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <netdb.h>
#include <signal.h>
#include <fcntl.h>
#include <errno.h>
#include <iostream>

Server::Server(): ROOT_(getenv("PWD"))
{	
	printf("Server started at port #%s with root directory as %s\n", PORT, ROOT_);
	
	startServer();
	make_non_blocking(listenfd_);
	// listen for incoming connections
	
	if (listen (listenfd_, CONNMAX) == -1 )
	{
		perror("listen error");
		exit(-1);
	}
	
	if((efd_ = epoll_create1(0)) == -1)
    {
      perror ("epoll_create");
      exit(-1);
    }
    
    event_.data.fd = listenfd_;
	event_.events = EPOLLIN | EPOLLOUT;
	int s = epoll_ctl (efd_, EPOLL_CTL_ADD, listenfd_, &event_);
	if (s == -1)
    {
      perror ("epoll_ctl error\n");
      exit(-1);
    }
    
    events_ = (epoll_event*)calloc (CONNMAX, sizeof(event_));
	/* Buffer where events are returned */
	//events_ = (epoll_event*) calloc (CONNMAX, sizeof(event_));
	
	/* The event loop */
	
	while (1)
    {
		int n, i;
		n = epoll_wait (efd_, events_, CONNMAX, -1);
		if(n < 0)
		{
			exit(-1);
		}
		
		for (int i = 0; i < n; ++i)
		{
			if ((events_[i].events & EPOLLERR) || (events_[i].events & EPOLLHUP) || (!(events_[i].events & EPOLLIN | EPOLLOUT)))
			{
				fprintf (stderr, "epoll error\n");
				close (events_[i].data.fd);
				continue;
			}
			
			else if (events_[i].data.fd == listenfd_)
			{
				while(1)
				{
					addrlen_ = sizeof clientaddr_;
					int client = accept (listenfd_, (struct sockaddr *) &clientaddr_, &addrlen_);
					if (client == -1)
					{
						if ((errno == EAGAIN) || (errno == EWOULDBLOCK))//We have processed all incoming connections.
						{
							break;
						}
						else
						{
							perror("accept() error");
							break;
						}
					}
					make_non_blocking(client);
					event_.data.fd = client;
					event_.events = EPOLLIN | EPOLLOUT;
					if(epoll_ctl(efd_, EPOLL_CTL_ADD, client, &event_) < 0)
					{
						fprintf(stderr, "epoll set insertation error: fd = %d", client);
						exit(-1);
					}
				}
				continue;
			}
			else
			{
				respond(events_[i].data.fd);
			}
		}
	}
	free (events_);
	close (listenfd_);
}
	
	
	

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Server::startServer()
{
	struct addrinfo hints, *res, *rp;
	// getaddrinfo for host
	memset (&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;						//for wildcard IP address 
	if (getaddrinfo(NULL, PORT, &hints, &res) != 0)
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
		listenfd_ = socket (rp->ai_family, rp->ai_socktype, 0);
		if (listenfd_ == -1) 
			continue;
		
		if (bind(listenfd_, rp->ai_addr, rp->ai_addrlen) == 0) 
			break; //success
			
		close(listenfd_);
	}
	if (rp == NULL) 					//no address succeeded 
	{
		fprintf(stderr, "Could not bind\n");
		exit(-1);
	}

	freeaddrinfo(res); 					//no longer needed
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Server::respond(int fd)
{
	int len = 10000;
	char mesg[len], *reqline[3], data_to_send[BYTES], path[100];
	int rcvd, bytes_read, ofd;

	memset( (void*)mesg, (int)'\0', len);

	rcvd = recv(fd, mesg, len, 0);

	if (rcvd < 0)    // receive error
		std::cout << "recv error: "<< strerror(errno) << std::endl;
	else if (rcvd == 0)    // receive socket closed
		fprintf(stderr,"Client disconnected upexpectedly.\n");
	else    // message received
	{
		printf("%s", mesg);
		reqline[0] = strtok (mesg, " \t\n");
		if (strncmp(reqline[0], "GET\0", 4) == 0)
		{
			reqline[1] = strtok (NULL, " \t");
			reqline[2] = strtok (NULL, " \t\n");
			if (strncmp( reqline[2], "HTTP/1.0", 8) != 0 && strncmp( reqline[2], "HTTP/1.1", 8) != 0 )
			{
				write(fd, "HTTP/1.0 400 Bad Request\n", 25);
			}
			else
			{
				if (strncmp(reqline[1], "/\0", 2) == 0)
					reqline[1] = (char*)"/index.html";        //if no file is specified, index.html will be opened by default (like it happens in APACHE)

				strcpy(path, ROOT_);
				strcpy(&path[strlen(ROOT_)], reqline[1]);
				printf("file: %s\n", path);

				if ((ofd = open(path, O_RDONLY)) != -1 )    //FILE FOUND
				{
					send(fd, "HTTP/1.0 200 OK\n\n", 17, 0);
					while ( (bytes_read = read(ofd, data_to_send, BYTES)) > 0 )
						write (fd, data_to_send, bytes_read);
				}
				else    write(fd, "HTTP/1.0 404 Not Found\n", 23); //FILE NOT FOUND
			}
		}
	}

	//Closing SOCKET
	shutdown (fd, SHUT_RDWR);         //All further send and recieve operations are DISABLED...
	close(fd);
	fd = -1;
}

void Server::make_non_blocking(int fd)
{
	int flags, s;
	
	flags = fcntl (fd, F_GETFL, 0);
	if (flags == -1)
		{
		perror ("fcntl error");
		exit(-1);
		}

	flags |= O_NONBLOCK;
	s = fcntl (fd, F_SETFL, flags);
	if (s == -1)
		{
		perror ("fcntl");
		exit(-1);
		}
}


