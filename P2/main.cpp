#include <iostream>
//#include <cstdio>
#include "copy.hpp"
#include "execute.hpp"
#include "handler.hpp"

int main(int argc, char *argv[]) 
{
	argv[1] = "/home/kukhterin/projects/hello/hello";
	argv[2] = "/home/kukhterin/projects/P2/hello_copy";
	int attempts = 0;
	int faults = 0;
	//char path[100];
	//char dest[100];
		
	//std::cout << "Insert full Programm1 address: ";
	//std::cin.getline(path, 100);  
	//std::cout << "Insert full destination address: ";
	//std::cin.getline(dest, 100); 
	
	//copy(path, dest);
	if(copy(argv[1], argv[2]))
	{
		while(attempts < 3)
		{
			faults += execute(argv[2], (*handler));
			attempts++;
		}
		//std::remove(argv[2]);
	
		std::cout << "\nSuccessfull executions: " << attempts - faults;
		std::cout << "\nExecution faults: " << faults << std::endl;
	}
	
	return 0;
}
