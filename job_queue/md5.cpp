#include <sstream>
#include <iostream>
#include <iomanip>//setfill
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <cstdio>
#include <cstdlib>
#include <string.h>
#include <openssl/md5.h>
#include "md5.hpp"

std::string md5_hash(std::string path)//char* path
{
	unsigned char uc_result[MD5_DIGEST_LENGTH];
	int file_descript;
    unsigned long file_size;
    char* file_buffer;

    file_descript = open(path.c_str(), O_RDONLY);//
    if(file_descript < 0) exit(-1);
	
	// Get the size of the file by its file descriptor
	struct stat statbuf;
	if(fstat(file_descript, &statbuf) < 0) 
		exit(-1);
	file_size = statbuf.st_size;
	///////////////////////////////////////////////////
	
	//Get MD5 sum

    file_buffer = (char*)(mmap(0, file_size, PROT_READ, MAP_SHARED, file_descript, 0)); //PROT_READ - can read data(prot - memory secure regime); MAP_SHARED - share map with other proccess(map is flag)
																						//mmap return ptr to place with mapped data;  
																						//void * mmap(void *start, size_t length, int prot , int flags, int fd, off_t offset); 

   MD5((unsigned char*) file_buffer, file_size, uc_result);
   munmap(file_buffer, file_size); 														//munmap return 0 in success
																						//int munmap(void *start, size_t length); 
	
	//Transfer unsigned char to hex string
   
	std::stringstream buffer;
	for (int i = 0; i < MD5_DIGEST_LENGTH; i++)
    {
        buffer << std::hex << std::setfill('0');
        buffer << std::setw(2)  << static_cast<unsigned>(uc_result[i]);
    }
	std::string result = buffer.str();
	//////////////////////////////////////
	
	return result;
}
