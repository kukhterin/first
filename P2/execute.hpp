#ifndef _LAUNCHER_
#define _LAUNCHER_

bool execute(char*, bool(*)(int)); //we pass to execute() the path to executable file and the pointer on handler function, that will obtain the result of execute() work and actually managed stuff after callback
	
#endif
