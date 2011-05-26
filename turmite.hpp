#ifndef TURMITE_HPP
#define TURMITE_HPP
#include "main.hpp"
#include "area.hpp"

using namespace std;

class turmite{
	public:
		turmite(int**,int,string,int,int,int opt_start_look=1);
		void left(void);						//move turmite left
		void right(void);						//move turmite right
		void go(void);							//go turmite forward

		bool goTurmit(int n_steps=1);					//make one step
		bool to_end(void);						//make all steps to end

		bool load(std::string fname="");		//load turmite frome file
		void reset(void);
		
		void show_brain(void);					//show turmite brain
		void show_info(void);					//show curent state info
		void get_x_y(int&,int&);
		int get_look(void);
		
		string get_filename(void);
			
	private:
		int **area;
		int n_pole;
	
		int start_x;			//start x position
		int start_y;			//start y position
		int start_look;
		int x;					//qrent x position
		int y;					//qrent y position
		int look;				//qrent look (0-^|1->|2-v|3-<)
		int steps;				//allowed steps
		
		string	q_state;		//qrent state
		int		q_line;			//qrent line in brain
		
		
		struct brain_line{		//turmite brain line
			string	state;		//Current state
			int		color;		//Current color
			int		Ncolor;		//New color
			int		rotate;		//rotate
			string	Nstate;		//New state
		};
		string brain_file;
		vector<brain_line> brain;
};

#endif
