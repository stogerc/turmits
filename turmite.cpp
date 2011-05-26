#include "turmite.hpp"
void turmite::get_x_y(int &gx,int &gy){
	gx=turmite::x;
	gy=turmite::y;
}

int turmite::get_look(void){
	return look;
}


string turmite::get_filename(void){
	return brain_file.substr(brain_file.find_last_of("/")+1);
}

turmite::turmite(int **area_n,int n_pole,string n_brain_file,
										int n_start_x,int n_start_y,
										int opt_start_look){
	brain_file.clear();
	brain_file=n_brain_file;
	load(brain_file);
	start_look=opt_start_look;
	x=start_x=n_start_x;
	y=start_y=n_start_y;
	look=1;
	turmite::area=area_n;
	turmite::n_pole=n_pole;
}

void turmite::show_info(){
	system("clear");
	clog<<"State:"<<q_state<<endl;
	clog<<"Wait for:"<<brain[q_line].color<<endl<<endl;
}

void turmite::show_brain(void){
	for(unsigned int i=0;i<brain.size();i++)
		cout<<brain[i].state<<" "
			<<brain[i].color<<" "
			<<brain[i].Ncolor<<" "
			<<brain[i].rotate<<" "
			<<brain[i].Nstate<<endl;
}

void turmite::reset(void){
	x=start_x;
	y=start_y;
	look=start_look;
}

bool turmite::goTurmit(int n_steps){
	unsigned int i;
	for(int j=0;j<n_steps;j++){
		if(steps==0)
			return 0;
			
		for(i=0;i<brain.size();i++){
			if(((brain[i].state==q_state)||brain[i].state=="<*>")
			&&((brain[i].color==area[x][y])||brain[i].color==-1)){

				if(brain[i].Ncolor!=-1)
					area[x][y]=brain[i].Ncolor;

				switch(brain[i].rotate){
					case -1:
						left();
						go();
					break;
				
					case 0:
						go();
					break;
				
					case 1:
						right();
						go();
					break;

					case 2:
						right();
						right();
						go();
					break;
				
					case -2:
						right();
						right();
						go();
					break;

				}
	//			clog<<brain[i].state<<endl;
				if(brain[i].Nstate!="<*>"){
					q_state.clear();
					q_state=brain[i].Nstate;
				}
				q_line=i;
				break;
			}
		}
		if(steps>0)
			steps--;
	}
	return 1;
}

bool turmite::to_end(void){
	if(steps>0)
		while(steps>0)
			goTurmit();
	else
		return 0;
}



bool turmite::load(string fname){//Переделать

	brain.clear();
	steps=-1;

	string newstr;
	string stemp;
	
	if(fname=="")
		fname=brain_file;
	else{
		brain_file.clear();
		brain_file=fname;
	}

	ifstream ifs(fname.c_str());
	if(!ifs.good()){
		return 0;
	}

	ifs>>newstr;
	char a;
	
	while(!ifs.eof()&&a!=-1){
		if(newstr.find_first_of(";")==0){
				while(ifs.get()!='\n');
		}else{
			if(newstr.find_first_of("#")==0){
				if(newstr.length()>1){
					stemp.clear();
					stemp=newstr.substr(newstr.find_first_of("#")+1);
					steps=atoi(stemp.c_str());
				}else
					ifs>>steps;
				while(ifs.get()!='\n');
			}else{
				brain_line nl;
				nl.state=newstr;
				ifs>>nl.color;
				ifs>>nl.Ncolor;
				ifs>>nl.rotate;
				ifs>>nl.Nstate;
				stemp.clear();
				stemp=nl.Nstate.substr(0,nl.Nstate.find_first_of(";"));
				nl.Nstate.clear();
				nl.Nstate=stemp;
	
				brain.push_back(nl);

				a=ifs.get();
				while(a!='\n'&&a!=-1)
					a=ifs.get();
				if(a==-1)
					fl_alert("Wrong file");
				
			}
		}
		newstr.clear();
		ifs>>newstr;
	}
	q_state.clear();
	if(brain.size()==0)
		fl_alert("Wrong file");
	else
		q_state=brain[0].state;
	
	q_line=0;
	return 1;
}



void turmite::go(void){
	switch(look){
		case 0:
	 		x=((x==0)?(n_pole-1):(x-1));
		break;

		case 1:
	 		y=(y==(n_pole-1)?0:(y+1));
	 	break;

		case 2:
	 		x=(x==(n_pole-1)?0:(x+1));
		break;
		
		case 3:
	 		y=((y==0)?(n_pole-1):(y-1));
	 	break;
	}
}


void turmite::left(void){
	look=((look==0)?3:(look-1));
}


void turmite::right(void){
	look=((look==3)?0:(look+1));
}

