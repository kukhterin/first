#include <iostream>
#include "Copy.hpp"
#include "Launcher.hpp"


int main(int argc, char *argv[]) 
{
	char path[100];
	char dest[100];
		
	std::cout << "Insert full Programm1 address: ";
	std::cin.getline(path, 100);  
	std::cout << "Insert full destination address: ";
	std::cin.getline(dest, 100); 
	
	Copy cp(path, dest);
	Launcher l(dest);
	
	return 0;
}
