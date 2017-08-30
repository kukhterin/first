#ifndef _LAUNCHER_
#define _LAUNCHER_

class Launcher
	{
	private:
		char path_name_[100]; 
		char dest_[100];
    
	public:
		Launcher();
		void set_path_name();
		void cp();
		void execute(); 
	};
	
#endif
