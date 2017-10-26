#include "Worker.hpp"
#include "NamedPipe.hpp"

//-pthread

int main (int argc, char ** argv)
{
	
	NamedPipe fifo;
	Worker worker(fifo);	
	
	return 0;
}