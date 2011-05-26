#ifndef BASEFIELD_HPP
#define BASEFIELD_HPP


class basefield{
	public:		
		virtual bool step(int steps=1){};					//make one step

		virtual bool load(std::string fname=""){};		//load frome file
		
		virtual void show_brain(void){};			//show turmite brain
		
		virtual string get_filename(void){};
		
		static int n_pole;
	protected:
		int **area;
		int **area_t;

		
		std::string brain_file;
};

#endif
