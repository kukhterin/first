#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <sys/wait.h> 
#include "execute.hpp"
  
int execute(char* file, int(*handler)(int errcode))
{
	int fault = 0;
	pid_t P1 = fork();
		
	if(P1 < 0)
	{
		std::cout << "\nFork error!";
		exit(1);
	}
    
	else if(P1 == 0)
	{
		execl(file, "./" , NULL);
		exit(0);   
	}
   
	else 
	{	  
		int status;
		pid_t pid;
		pid = waitpid(P1, &status, 0);
		fault = handler(status);
	}
}
