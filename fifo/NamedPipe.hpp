#include <sys/types.h>
#include <string>

#ifndef _NAMED_PIPE_
#define _NAMED_PIPE_
#define NAMEDPIPE_NAME "/tmp/my_named_pipe"
#define BUFSIZE			100
#define RIGHTS			0777

class NamedPipe
{
private:
	NamedPipe(const NamedPipe&);
	void operator=(const NamedPipe&);
	void create();
	int fd_;
	size_t len_;
    char buf_[BUFSIZE];
	
public:
	NamedPipe();
	~NamedPipe();
	std::string answer();	
	
};

#endif
