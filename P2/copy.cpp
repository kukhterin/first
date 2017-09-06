#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <sys/stat.h>
#include <sys/types.h>
#include "copy.hpp"

bool copy(char* source, char* dest)
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
		return false;
	}
	
	output_f_d = open(dest, O_RDONLY); // Trying to open dest
	if(output_f_d == -1) // if dest doesn't exists
	{
		open_flags = O_CREAT | O_RDWR | O_TRUNC; // Create dest
		file_perms = S_IRWXU | S_IRWXG |S_IRWXO;
		output_f_d = open(dest, open_flags, file_perms);

		if(output_f_d == -1)
		{
			std::cerr << "Copy error!" << std::endl;
			std::remove (dest); //delete file, if can't copy successfully
			return false;
		}
	
		while((num_read = read (input_f_d, buf, BUF_SIZE)) > 0)
		{
			if(write(output_f_d, buf, num_read) != num_read)
			{
			std::cerr << "Couldn't write whole buffer!" << std::endl;
			std::remove (dest); //delete file, if cant copy successfully
			return false;
			}
			if(num_read == -1)
			{
			std::cerr << "Reading error!" << std::endl;
			std::remove (dest); //delete file, if cant copy successfully
			return false;
			}
		}	
	}
	
	else //if dest already exist
	{
		char buf2[BUF_SIZE];
		
		struct stat attr1;
		struct stat attr2;
		stat(source, &attr1);
		stat(dest, &attr2);
		
		if(attr1.st_mode != attr2.st_mode)
		{
			std::cerr << "Destination folder already contain different type file with the same name!" << std::endl;
			return false;
		}
		
		else
		{
			while((num_read = read(input_f_d, buf, BUF_SIZE)) > 0)
			{	
				read(output_f_d, buf2, BUF_SIZE);
				if(std::memcmp(&buf, &buf2, BUF_SIZE) != 0) // compare source and dest
				{
				std::cerr << "Destination folder already contain different file with the same name!" << std::endl;
				return false;
				}
			}
		}
		std::cout << "Requested destination file already exist!" << std::endl;
		return true;	
	}
	
  
	if(close(input_f_d) == -1)
		
	{
		std::cerr << "Error in closing input!";
		return false;
	}
	if(close(output_f_d) == -1)
	{
	    std::cerr << "Error in closing output!";
		return false;
	}
	  
	std::cout << "Copy process completed successfully" << std::endl;
	return true;
}
