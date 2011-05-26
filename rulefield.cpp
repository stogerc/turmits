#include "main.hpp"
#include "basefield.hpp"
#include "rulefield.hpp"


int rulefield::n_pole;

string rulefield::get_filename(void){
	return brain_file.substr(brain_file.find_last_of("/")+1);
}


int rulefield::bin2dec(int bin){
	int dec=0;
	for(int i=0;i<3;i++){
		bool onebin;
		onebin=bin%10;
		dec+=onebin<<i;
		bin/=10;
	}
	return dec;
}

rulefield::rulefield(int **area_n,int n_pole,string n_brain_file){
	brain_file.clear();
	brain_file=n_brain_file;

	rulefield::area=area_n;
	rulefield::n_pole=n_pole;

	load(brain_file);
	
	area_t=new int *[n_pole];
	for(int i=0;i<n_pole;i++){
		area_t[i]=new int [n_pole];
	}
};

bool rulefield::load(string fname){//Переделать

//	brain.clear();
	program.clear();
	program.resize(8);
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
	int rule,new_color;
	ifs>>rule;
	char a;
	while(!ifs.eof()&&a!=-1){
		ifs>>new_color;
		program[bin2dec(rule)]=new_color;

		a=ifs.get();
		while(a!='\n'&&a!=-1)
			a=ifs.get();
		if(a==-1)
			fl_alert("Wrong file");
		ifs>>rule;

	}
	return 1;
}

void rulefield::show_brain(void){
	for(unsigned int i=0;i<program.size();i++)
		cout<<i<<" "
			<<program[i]<<endl;
}

bool rulefield::step(int steps){
//	for(int some_steps=0;some_steps<steps;some_steps++){
		for(int i=0;i<n_pole;i++){
			memcpy(area_t[i],area[i],sizeof(int)*n_pole);
		}

		for(int i=0;i<n_pole;i++){
			for(int j=0;j<n_pole;j++){
				if(area_t[i][j]!=0)
					continue;
					area[i][j]=program[neighbors(i,j)];
			}
		}
//	}
	return 1;
}

int rulefield::neighbors(int x,int y){
	int i;
	int ncl=0;
	for(i=-1;i<2;i++){
			int xtt=x-1;
			if(xtt==-1)
				xtt=n_pole-1;
			if(xtt==n_pole)
				xtt=0;
				
			int ytt=y+i;
			if(ytt==-1)
				ytt=n_pole-1;
			if(ytt==n_pole)
				ytt=0;
			ncl+=area_t[xtt][ytt]*pow(10,2-(i+1));
	}
//	clog<<"-"<<x<<"."<<y<<":"<<ncl<<endl;
//	clog<<ncl;
	return bin2dec(ncl);
}
