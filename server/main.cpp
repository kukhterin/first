#include <iostream>
#include <netdb.h>

#include "Server.hpp"

#define CONNMAX 1024
#define PORT "80" //standart http port

// http://10.31.36.250:80/      
// http://10.31.36.247:8080/   

int main(int argc, char **argv) 
{
   
	Server serv(AI_PASSIVE, (char*)PORT, CONNMAX);
	
}
