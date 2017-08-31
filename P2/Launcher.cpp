#include <iostream>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <cstdlib>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h> 
#include <fcntl.h>
#include <map>
#include <utility>
#include <string>
#include "Launcher.hpp"

Launcher::Launcher(char* file) : file_(file)
{
	execute();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
    
void Launcher::execute()
{
	pid_t P1;
	
	size_t attempt = 1;
	const size_t repeat = 3;
	size_t successfull_execution = 0;
	size_t execution_fault = 0;
	std::string result;
	std::string temp;
	std::map<size_t, std::string>  record;
  
	while(attempt <= repeat)
	{
		pid_t P1 = fork();
		
		if(P1 < 0)
		{
			result = "Fork error!";
			record.insert(std::pair<size_t, std::string>(attempt, result));
			execution_fault++;
			exit(1);
		}
    
		if(P1 == 0)
		{
			execl(file_, "./" , NULL);
			exit(0);   
		}
   
		else 
		{	  
			int status;
			pid_t pid;
			pid = waitpid(P1, &status, 0);
			//std::cout << "\nNow run parent process, PID = " << getpid() << ", Child's PID = " << P1;
      
	  
			if(WIFEXITED(status))
			{
				result = "Sucessfull execution";
				record.insert(std::pair<int, std::string>(attempt, result));
				successfull_execution++;
			}
      
			else if(WIFSIGNALED(status))
			{
				temp = strsignal(WTERMSIG(status));
				result = "Execution was killed by signal: " + temp;
				record.insert(std::pair<int, std::string>(attempt, result));
				execution_fault++;
			}
      
			#ifdef WCOREDUMP
			else if(WCOREDUMP(status))
			{
				result = "Execution faild: core dumped";
				record.insert(std::pair<int, std::string>(attempt, result));
				execution_fault++;
			}
			#endif
       
			else if(WIFSTOPPED(status))
			{
				temp = strsignal(WSTOPSIG(status));
				result = "Execution was stopped by signal: " + temp;
				record.insert(std::pair<int, std::string>(attempt, result));
				execution_fault++;
			}
      
			#ifdef WIFCONTINUED
			else if(WIFCONTINUED(status))
			{
				result = "Execution don't normally completed, process continued";
				record.insert(std::pair<int, std::string>(attempt, result));
				execution_fault++;
			}	
			#endif
      
			else
			{
				result = "Something unexpected happend";
				record.insert(std::pair<int, std::string>(attempt, result));
				execution_fault++;
			}	
		}
	attempt += 1;
	}
	
	std::cout << "\nSuccessfull execution: " << successfull_execution << ", faults: " << execution_fault << std::endl;
	std::cout << "More details: " << std::endl;
	for (std::map<size_t, std::string>::iterator it = record.begin(); it != record.end(); ++it)
	{
		std::cout << it->first << " : "<< it->second << std::endl;
	}
}
