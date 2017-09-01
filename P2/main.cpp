#include <iostream>
#include <cstdio>
#include "copy.hpp"
#include "execute.hpp"
#include "handler.hpp"

int main(int argc, char *argv[]) 
{
	int attempts = 0;
	int faults = 0;
	char path[100];
	char dest[100];
		
	std::cout << "Insert full Programm1 address: ";
	std::cin.getline(path, 100);  
	std::cout << "Insert full destination address: ";
	std::cin.getline(dest, 100); 
	
	copy(path, dest);
	while(attempts < 3)
	{
		faults += execute(dest, (*handler));
		attempts++;
	}
	std::remove(dest);
	std::cout << "\nSuccessfull executions: " << attempts - faults;
	std::cout << "\nExecution faults: " << faults << std::endl;
	
	return 0;
}
