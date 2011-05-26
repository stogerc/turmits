#ifndef AREA_HPP
#define AREA_HPP
#include "main.hpp"
class field{
	public:
		field(int);
		void clear(int new_color=0);
	
		int color(int,int);
		void color(int,int,int);
		void draw(int,int,int,int);
		int** get_ar(void);
		void resize(int);
		int n_size(void);
	
	private:
		int **area;
		int n_pole;
};

#endif
