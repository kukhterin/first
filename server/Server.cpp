#include "Server.hpp"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<netdb.h>
#include<signal.h>
#include<fcntl.h>

Server::Server(): ROOT_(getenv("PWD")), slot_(0)
{
	printf("Server started at port #%s with root directory as %s\n", PORT, ROOT_);
	// Setting all elements to -1: signifies there is no client connected
	int i;
	for (i=0; i<CONNMAX; i++)
		clients_[i]=-1;
	startServer();

	// ACCEPT connections
	while (1)
	{
		addrlen_ = sizeof(clientaddr_);
		clients_[slot_] = accept (listenfd_, (struct sockaddr *) &clientaddr_, &addrlen_);

		if (clients_[slot_] < 0 )
			perror("accept() error");
		else
		{
			if(fork() == 0)
			{
				respond(slot_);
				exit(0);
			}
		}

		while (clients_[slot_]!=-1) 
			slot_ = (slot_+1)%CONNMAX;
	}	
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

	// listen for incoming connections
	if ( listen (listenfd_, CONNMAX) != 0 )
	{
		perror("listen() error");
		exit(-1);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Server::respond(int n)
{
	char mesg[1000], *reqline[3], data_to_send[BYTES], path[100];
	int rcvd, fd, bytes_read;

	memset( (void*)mesg, (int)'\0', 1000 );

	rcvd = recv(clients_[n], mesg, 1000, 0);

	if (rcvd < 0)    // receive error
		fprintf(stderr,("recv() error\n"));
	else if (rcvd==0)    // receive socket closed
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
				write(clients_[n], "HTTP/1.0 400 Bad Request\n", 25);
			}
			else
			{
				if (strncmp(reqline[1], "/\0", 2) == 0)
					reqline[1] = "/index.html";        //if no file is specified, index.html will be opened by default (like it happens in APACHE)

				strcpy(path, ROOT_);
				strcpy(&path[strlen(ROOT_)], reqline[1]);
				printf("file: %s\n", path);

				if ((fd = open(path, O_RDONLY)) != -1 )    //FILE FOUND
				{
					send(clients_[n], "HTTP/1.0 200 OK\n\n", 17, 0);
					while ( (bytes_read = read(fd, data_to_send, BYTES)) > 0 )
						write (clients_[n], data_to_send, bytes_read);
				}
				else    write(clients_[n], "HTTP/1.0 404 Not Found\n", 23); //FILE NOT FOUND
			}
		}
	}

	//Closing SOCKET
	shutdown (clients_[n], SHUT_RDWR);         //All further send and recieve operations are DISABLED...
	close(clients_[n]);
	clients_[n]=-1;
}

