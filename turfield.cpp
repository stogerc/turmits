/*
Добавить соседство по Нейману.
*/
#include <iostream>
#include "turfield.hpp"


string turfield::get_filename(void){
	return brain_file.substr(brain_file.find_last_of("/")+1);
}

turfield::turfield(int **area_n,int n_pole,string n_brain_file){
	brain_file.clear();
	brain_file=n_brain_file;

	turfield::area=area_n;
	turfield::n_pole=n_pole;
	load(brain_file);

	area_t=new int *[n_pole];
	for(int i=0;i<n_pole;i++){
		area_t[i]=new int [n_pole];
	}

};

bool turfield::load(string fname){//Переделать

	brain.clear();
	
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
	int color;
	ifs>>color;
	char a;
	while(!ifs.eof()&&a!=-1){

		brain_line nl;
		nl.color=color;
		ifs>>nl.n_neigh;
		ifs>>nl.neigh_color;
		ifs>>nl.new_color;
		brain.push_back(nl);
		a=ifs.get();
		while(a!='\n'&&a!=-1)
			a=ifs.get();
		if(a==-1)
			fl_alert("Wrong file");
		ifs>>color;
	}

	return 1;
}

void turfield::show_brain(void){
	for(unsigned int i=0;i<brain.size();i++)
		cout<<brain[i].color<<" "
			<<brain[i].n_neigh<<" "
			<<brain[i].neigh_color<<" "
			<<brain[i].new_color<<endl;
}

bool turfield::find_cifr(string chislo,int cifra){
	for(int i=0;i<chislo.size();i++)
		if(chislo[i]==cifra+48)
			return 1;
	return 0;
}

bool turfield::step(int steps){

	for(int i=0;i<n_pole;i++){
		for(int j=0;j<n_pole;j++){
			area_t[i][j]=area[i][j];
		}	
	}
	for(int i=0;i<n_pole;i++){
		for(int j=0;j<n_pole;j++){
//			switch(area[i][j]){
//				case 0:{
//					if(neighbors(i,j,1)==2)
//						area[i][j]=1;
//				}break; 
//				
//				case 1:{
//					int neighb=neighbors(i,j,1);
//					if(!(neighb==3||neighb==4||neighb==5))
//						area[i][j]=2;
//				}break;
//				
//				case 2:{
//					int neighb=neighbors(i,j,2);
//					if(!(neighb==3||neighb==4||neighb==5))
//						area[i][j]=3;
//				}break; 
//				
//				case 3:{
//					int neighb=neighbors(i,j,3);
//					if(!(neighb==3||neighb==4||neighb==5))
//						area[i][j]=0;
//				}break;
//			}
			for(int k=0;k<brain.size();k++){
				if(area_t[i][j]==brain[k].color){
					int neighs=neighbors(i,j,brain[k].neigh_color);
					if((find_cifr(brain[k].n_neigh,
					neighs)^brain[k].n_neigh[0]=='!')||
					((brain[k].n_neigh=="-1"&&neighs>0)
					||brain[k].neigh_color==-1)){
						area[i][j]=brain[k].new_color;
						break;
					}
				}else
					continue;
			}
		}
	}

	return 1;
}

int turfield::neighbors(int x,int y,int color){
	int ncl=0,i,j;
	for(i=-1;i<2;i++){
		for(j=-1;j<2;j++){
			if(i==0&&j==0)continue;
				int xtt=x+i;
				if(xtt==-1)
					xtt=n_pole-1;
				if(xtt==n_pole)
					xtt=0;
				
				int ytt=y+j;
				if(ytt==-1)
					ytt=n_pole-1;
				if(ytt==n_pole)
					ytt=0;
				if(area_t[xtt][ytt]==color)
					ncl++;
		}
	}
//	clog<<color<<"-"<<x<<"."<<y<<":"<<ncl<<endl;
	return ncl;
}



int turfield::n_znak(int chislo){
	return chislo/10?1+n_znak(chislo/10):1;
}

//int main(void){
//	turfield myturfield(NULL, 100, "turfield_prog");
//	myturfield.show_brain();
//	return 0;
//}
