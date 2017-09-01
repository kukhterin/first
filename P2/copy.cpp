#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <cstdlib>
#include "copy.hpp"

void copy(char* source, char* dest)
{
	const size_t BUF_SIZE = 1024;
	char buf[BUF_SIZE];
	ssize_t num_read;
	int input_f_d, output_f_d, open_flags;
	mode_t file_perms;
  
	input_f_d = open(source, O_RDONLY);
	if(input_f_d == -1)
	{
		std::cerr << "Can't open source file!" << std::endl;
		exit(1);
	}
  
	open_flags = O_CREAT | S_IRWXU | O_RDWR | O_TRUNC;
	file_perms = S_IRWXU | S_IRWXG |S_IRWXO;
	output_f_d = open(dest, open_flags, file_perms);
	
	if(output_f_d == -1)
	{
		std::cerr << "Copy error!" << std::endl;
		exit(1);
	}
  
	while((num_read = read (input_f_d, buf, BUF_SIZE)) > 0)
	{
		if(write(output_f_d, buf, num_read) != num_read)
		{
		std::cerr << "Couldn't write whole buffer!" << std::endl;
		exit(1);
		}
		if(num_read == -1)
		{
		std::cerr << "Reading error!" << std::endl;
		exit(1);
		}
	}
	
	if(close(input_f_d) == -1)
	{
		std::cerr << "Error in closing input!";
	    exit(1);
	}
	if(close(output_f_d) == -1)
	{
	    std::cerr << "Error in closing output!";
	    exit(1);
	}
	  
	std::cout << "Copy process completed successfully" << std::endl;	  
}
