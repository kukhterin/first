#include <iostream>
#include <string.h>
#include <cstdlib>
#include "handler.hpp"
#include "execute.hpp"

bool handler(int errcode)
{ 
	
	if(WIFEXITED(errcode))
	{
		std::cout << "Sucessfull execution" << std::endl;
		return true;
	}
      
	else if(WIFSIGNALED(errcode))
	{
		std::cout << "\nExecution was killed by signal: " << strsignal(WTERMSIG(errcode));
		return false;
	}
      
	#ifdef WCOREDUMP
	else if(WCOREDUMP(errcode))
	{
		std::cout << "\nExecution faild: core dumped";
		return false;
	}
	#endif
       
	else if(WIFSTOPPED(errcode))
	{
		std::cout << "\nExecution was stopped by signal: " << strsignal(WSTOPSIG(errcode));
		return false;
	}
	
	#ifdef WIFCONTINUED
	else if(WIFCONTINUED(errcode))
	{
		std::cout << "\nExecution don't normally completed, process continued";
		return false;
	}	
	#endif
      
	else
	{
		std::cout << "\nSomething unexpected happend";
		return false;
	}
}
