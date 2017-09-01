#include <iostream>
#include <string.h>
#include <cstdlib>
#include "handler.hpp"
#include "execute.hpp"

int handler(int errcode)
{ 
	int execution_fault = 0;
	
	if(WIFEXITED(errcode))
	{
		std::cout << "Sucessfull execution" << std::endl;
	}
      
	else if(WIFSIGNALED(errcode))
	{
		std::cout << "\nExecution was killed by signal: " << strsignal(WTERMSIG(errcode));
		execution_fault++;
	}
      
	#ifdef WCOREDUMP
	else if(WCOREDUMP(errcode))
	{
		std::cout << "\nExecution faild: core dumped";
		execution_fault;
	}
	#endif
       
	else if(WIFSTOPPED(errcode))
	{
		std::cout << "\nExecution was stopped by signal: " << strsignal(WSTOPSIG(errcode));
		execution_fault++;
	}
	
	#ifdef WIFCONTINUED
	else if(WIFCONTINUED(errcode))
	{
		std::cout << "\nExecution don't normally completed, process continued";
		execution_fault++;
	}	
	#endif
      
	else
	{
		std::cout << "\nSomething unexpected happend";
		execution_fault++;
	}
	return execution_fault;
}
