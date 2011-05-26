#ifndef RULEFIELD_HPP
#define RULEFIELD_HPP
#include "main.hpp"

class rulefield:public basefield{
	public:
		rulefield(int**,int,string);
		
		bool step(int steps=1);					//make one step

		bool load(std::string fname="");		//load turmite frome file
		
		void show_brain(void);					//show turmite brain
			
		int neighbors(int,int);
		
		int bin2dec(int);
		
		static int n_pole;
		
		string get_filename(void);

	private:
		int **area;
		int **area_t;
		vector<int> program;

//		struct brain_line{		//turmite brain line
//			string		rule;		//Current color
//			int		new_color;	//New color
//		};
		
		string brain_file;
//		vector<brain_line> brain;

};

#endif
