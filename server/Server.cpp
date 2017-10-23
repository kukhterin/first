#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <netdb.h>
#include <signal.h>
#include <fcntl.h>
#include <errno.h>
#include <iostream>
#include <utility>
#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>

#include "Server.hpp"

Server::Server(): ROOT_(getenv("PWD"))
{
	start_server();
	/* The event loop */
	server_wait();
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Server::~Server()
{
	free (events_);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Server::start_server()
{
	listenfd_.create_and_bind(AI_PASSIVE, (char*)PORT);
	
	printf("Server started at port #%s with root directory as %s\n", PORT, ROOT_);
	
	listenfd_.make_non_blocking();
	
	// listen for incoming connections
		listenfd_.sock_listen(CONNMAX);
	
	if((efd_ = epoll_create(CONNMAX)) == -1)
    {
      perror ("epoll_create");
      exit(-1);
    }
    
    event_.data.fd = (int)listenfd_;
	event_.events = EPOLLIN; // EPOLLIN | EPOLLOUT | EPOLLET
	int s = epoll_ctl (efd_, EPOLL_CTL_ADD, (int)listenfd_, &event_);
	if (s == -1)
    {
      perror ("epoll_ctl error\n");
      exit(-1);
    }
    
    events_ = (epoll_event*)calloc (CONNMAX, sizeof(event_));
	/* Buffer where events are returned */
	
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Server::server_wait()
{
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
				
				std::cout << "Epoll error" << strerror(errno) << std::endl;
				close (events_[i].data.fd);
				continue;
			}
			
			else if (events_[i].data.fd == (int)listenfd_)
			{
				while(1)
				{
					
					int client_fd = listenfd_.sock_accept();
					if(client_fd == -1)
						break;
				
					event_.data.fd = client_fd;
					event_.events = EPOLLIN;
					if(epoll_ctl(efd_, EPOLL_CTL_ADD, client_fd, &event_) < 0)
					{
						fprintf(stderr, "epoll set insertation error: fd = %d", client_fd);
						exit(-1);
					}
					Client new_client;					
					c_map_.insert(std::pair<int, Client>(client_fd, new_client));
				}
				continue;
			}
			else
			{
				respond(events_[i].data.fd);
				continue;
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Server::respond(const int fd)
{	
		
	if((c_map_[fd].get_file()) == "")
	{
	
		int len = 1024;
		char mesg[len], *reqline[3], path[100];
		int rcvd;

		memset( (void*)mesg, (int)'\0', len);
		
		rcvd = recv(fd, mesg, len, 0);

		if ((rcvd == -1) | (rcvd == 0))    // receive error | receive socket closed
		{
			if (errno != EAGAIN)
			{
				std::cout << "recv error: "<< strerror(errno) << std::endl;
			}
			shutdown (fd, SHUT_RDWR);
			return;
			
		}
		
		else
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
					c_map_.erase(fd);
					shutdown (fd, SHUT_RDWR);
					close(fd);
					return;
				}
				else
				{
					if (strncmp(reqline[1], "/\0", 2) == 0)
						reqline[1] = (char*)"/index.html";        //if no file is specified, index.html will be opened by default (like it happens in APACHE)
					strcpy(path, ROOT_);
					strcpy(&path[strlen(ROOT_)], reqline[1]);
					printf("file: %s\n", path);
									
					if (c_map_[fd].set_file(path))    //FILE FOUND
						send(fd, "HTTP/1.0 200 OK\n\n", 17, 0);
					else    
					{
						write(fd, "HTTP/1.0 404 Not Found\n", 23); //FILE NOT FOUND
						c_map_.erase(fd);
						shutdown (fd, SHUT_RDWR);
						close(fd);
						return;
					}
				}
			}
		}
	}
	
	c_map_[fd].send(fd);
	
	if((c_map_[fd].is_ready()))
	{
		shutdown (fd, SHUT_RDWR);
		close(fd);
		c_map_.erase(fd);

	}
	
	return;
}

