#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <sys/wait.h> 
#include "execute.hpp"
  
bool execute(char* file, bool(*handler)(int errcode)) 
{
	pid_t P1 = fork();
		
	if(P1 < 0)
	{
		std::cout << "\nFork error!";
		return false;
	}
    
	else if(P1 == 0)
	{
		execl(file, NULL);
		exit(0);   
	}
   
	else 
	{	  
		int status;
		pid_t pid;
		pid = waitpid(P1, &status, 0);
		return handler(status); // handler return false in case of error, so in this place we combine the making the callback, the sending int the status to the handler and also receive the handlers returning value
	}
}
