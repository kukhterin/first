#ifndef _COPY_
#define _COPY_

class Copy
{
private:
	char* source_; 
	char* dest_;
    
public:
	Copy(char*, char*);
	void cp(); 
};
	
#endif
