#include "main.hpp"
#include "turmite.hpp"
#include "area.hpp"
//#include "glut.hpp"
#include "fltk.hpp"
#include "turfield.hpp"
#include "basefield.hpp"
#include "rulefield.hpp"
using namespace std;


static const char *opt_string = "t:f:r:c:o:vh?";


int		opt_n_field=10;	//NxN area
int		opt_sq_size=10;
int		opt_sp_size=1;
bool	opt_kill_end=0;
int		opt_start_x=opt_n_field/2;
int		opt_start_y=opt_n_field/2;
bool	opt_is_pause=false;
int		opt_go_per_step=100;
int		opt_draw_color=1;
bool	opt_is_show_turmite=1;
int		opt_timer=0;



vector<turmite> opt_turmite_v;
field myar(opt_n_field);

vector<basefield*> opt_basefield_v;
	vector<turfield> turfield_v;
	vector<rulefield> rulefield_v;

	
////////////////////////////////////////////////////

int load_config(string configFile){
	string newstr;
	string stemp;
	
	ifstream ifs(configFile.c_str());
	if(ifs.fail()){
		cerr<<"Fail to load config"<<endl;
		return 0;
	}
	ifs>>newstr;
	
	while(!ifs.eof()){
		if(newstr.find_first_of(";")==0){
				while(ifs.get()!='\n');
		}else{
			if(newstr=="AREA_SIZE")
				ifs>>opt_n_field;
			if(newstr=="SQUARE_SIZE")
				ifs>>opt_sq_size;
			if(newstr=="GAP_SIZE")
				ifs>>opt_sp_size;
			if(newstr=="EXIT_IF_NO_STEPS")
				ifs>>opt_kill_end;
			if(newstr=="START_X_POSITION")
				ifs>>opt_start_x;
			if(newstr=="START_Y_POSITION")
				ifs>>opt_start_y;
			if(newstr=="GO_PER_STEP")
				ifs>>opt_go_per_step;
			if(newstr=="START_WITH_PAUSE")
				ifs>>opt_is_pause;
			if(newstr=="DRAW_COLOR")
				ifs>>opt_draw_color;
			if(newstr=="SHOW_TURMITE")
				ifs>>opt_is_show_turmite;
			if(newstr=="ANIMATION_SPEED")
				ifs>>opt_timer;
					
			while(ifs.get()!='\n');
				
		}
		newstr.clear();
		ifs>>newstr;
	}
	if(opt_start_x==-1)
		opt_start_x=opt_n_field/2;
	if(opt_start_y==-1)
		opt_start_y=opt_n_field/2;
	if(opt_timer<=0)
		opt_timer=1;
	//Добавить защиту от дурака для остальных параметров
	ifs.close();
	return 1;
}

void show_help(void){
	cout<<"Usage: turm [OPTION]... File..."<<endl
		<<"Example: turm -t brains/my"<<endl<<endl
		<<"OPTIONS:"<<endl
		<<"-t, --turmite"<<setw(20)<<"Run turmite file"<<endl
		<<"-f, --turfield"<<setw(20)<<"Run turfield file"<<endl;
		
		
}

void add_turmite(string filename){
	turmite myturm(myar.get_ar(),opt_n_field,filename,
					opt_start_x,opt_start_y);
	opt_turmite_v.push_back(myturm);
}
void add_turfield(string filename){
	turfield mytfield(myar.get_ar(),opt_n_field,filename);
	turfield_v.push_back(mytfield);
	opt_basefield_v.push_back((basefield*)&turfield_v[turfield_v.size()-1]);

}
void add_rule(string filename){
	rulefield myrufield(myar.get_ar(),opt_n_field,filename);
	rulefield_v.push_back(myrufield);
	opt_basefield_v.push_back((basefield*)&rulefield_v[rulefield_v.size()-1]);
}


int main(int Narg,char **arg){
	string configfile="./config";
	int opt = 0;
	int longIndex = 0;

	load_config(configfile);
	myar.resize(opt_n_field);
	opt=getopt_long( Narg, arg, opt_string, longOpts, &longIndex );
	while(opt!= -1) {
		switch( opt ) {
			case 't':
				add_turmite(optarg);
			break;
			
			case 'f':
				add_turfield(optarg);
			break;
			
			case 'r':
				add_rule(optarg);
			break;
			
				
			case 'c':
				configfile.clear();
				configfile=optarg;
			break;
				
			case 'o':
				clog<<optarg<<endl;
			break;
				
			case 'v':

			break;
				
			case 'h':	/* fall-through is intentional */
				show_help();
				exit(0);
			break;
			
			case '?':

				break;

			case 0:		/* long option without a short arg */
				clog<<"wtf?"<<endl;
			break;
				
			default:
				/* You won't actually get here. */
			break;
		}
		
		opt = getopt_long( Narg, arg, opt_string, longOpts, &longIndex );
	}
	fltk_cycle(opt_basefield_v,opt_start_x,opt_start_y,
				opt_turmite_v,&myar,opt_sq_size,opt_sp_size,opt_n_field,
				opt_go_per_step,opt_draw_color,opt_is_show_turmite,
				opt_timer);

//	glut_cycle(opt_turmite_v,&myar,opt_sq_size,opt_sp_size,opt_n_field,
//				opt_go_per_step,opt_draw_color,opt_is_show_turmite,
//				opt_timer);
	
	return 0;
}
