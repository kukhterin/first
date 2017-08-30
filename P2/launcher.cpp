#include <iostream>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <cstdlib>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h> 
#include <fcntl.h>
#include "launcher.hpp"

//source = "/home/kukhterin/projects/hello/hello";

Launcher::Launcher()
{
	set_path_name();
	cp();
	execute();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////

void Launcher::set_path_name()
{
	std::cout << "Insert full Programm1 address: ";
	std::cin.getline(path_name_, 100);  
	std::cout << "Insert full destination address: ";
	std::cin.getline(dest_, 100); 
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

void Launcher::cp()
{
	const size_t BUF_SIZE = 1024;
	char buf[BUF_SIZE];
	ssize_t num_read;
	int input_f_d, output_f_d, open_flags;
	mode_t file_perms;
  
	input_f_d = open(path_name_, O_RDONLY);
	if(input_f_d == -1)
	{
		std::cerr << "Can't open source file!";
		return;
	}
  
	open_flags = O_CREAT | S_IRWXU | O_RDWR | O_TRUNC; //S_IRWXU - permission to execute(open mode)
	file_perms = S_IRWXU | S_IRWXG |S_IRWXO; //S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;  
	output_f_d = open(dest_, open_flags, file_perms);
	
	if(output_f_d == -1)
	{
		std::cerr << "Can't make destination file or file already exist!" << std::endl;
		return;
	}
  
	while((num_read = read (input_f_d, buf, BUF_SIZE)) > 0)
	{
		if(write(output_f_d, buf, num_read) != num_read)
		{
		std::cerr << "Couldn't write whole buffer!" << std::endl;
		return;
		}
		if(num_read == -1)
		{
		std::cerr << "Reading error!";
		return;
		}
	}
	
	if(close(input_f_d) == -1)
	{
		std::cerr << "Error in closing input!";
	    return;
	}
	if(close(output_f_d) == -1)
	{
	    std::cerr << "Error in closing output!";
	    return;
	}
	  
	std::cout << "Copy process completed successfully" << std::endl;	  
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
    
void Launcher::execute()
{
	pid_t P1; // descriptor for P1 process
	int repeat = 3;
  
	while(repeat)
	{
		pid_t P1 = fork();
		
		if(P1 < 0)
		{
			std::cerr << "\nFork error!" << std::endl;
			exit(-1);
		}
    
		if(P1 == 0)
		{
			execl(dest_, "./" , NULL);
			exit(EXIT_SUCCESS);   
		}
   
		else 
		{	  
			int status;
			pid_t pid;
			pid = waitpid(P1, &status, 0);
			std::cout << "\nNow run parent process, PID = " << getpid() << ", Child's PID = " << P1;
      
	  
			if(WIFEXITED(status))
			{
				std::cout << "\nChild exited normally with exit status = " << WEXITSTATUS(status) << std::endl;
			}
      
			else if(WIFSIGNALED(status))
			{
				std::cout << "\n Child killed by signal = " << WTERMSIG(status) << " " << strsignal(WTERMSIG(status)) << std::endl;
			}
      
			#ifdef WCOREDUMP
			else if(WCOREDUMP(status))
			{
				std::cout << "\n Core dumped" << std::endl;
			}
			#endif
       
			else if(WIFSTOPPED(status))
			{
				std::cout << "\n Child stopped by signal = " << WSTOPSIG(status) << " " << strsignal(WSTOPSIG(status)) << std::endl;
			}
      
			#ifdef WIFCONTINUED
			else if(WIFCONTINUED(status))
			{
				std::cout << "\n Child continued" << std::endl;
			}	
			#endif
      
			else
			{
				std::cout << "\n Something unexpected happend " << (unsigned int)status << std::endl;
			}	
		}
	repeat -= 1;
	}
}