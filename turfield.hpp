#ifndef TURFIELD_HPP
#define TURFIELD_HPP
#include "main.hpp"
#include "basefield.hpp"

class turfield:public basefield{
	public:
		turfield(int**,int,string);
		
		bool step(int steps=1); 	//make some steps

		bool load(std::string fname="");		//load turfield frome file
		
		void show_brain(void);					//show turmite brain
	
		bool find_cifr(string,int);
		int n_znak(int);
		
		int neighbors(int,int,int);
		
		string get_filename(void);

	private:
		int n_pole;
		int **area;
		int **area_t;


		struct brain_line{		//turmite brain line
			int		color;		//Current color
			string	n_neigh;	//Num neighbors
			int		neigh_color;//Color of neighbors
			int		new_color;	//New color
		};
		string brain_file;
		vector<brain_line> brain;
};


#endif
