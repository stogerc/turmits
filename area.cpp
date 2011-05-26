#include "area.hpp"

field::field(int n_pole){
	field::n_pole=n_pole;
}

void field::clear(int new_color){
	for(int i=0;i<n_pole;i++)
		for(int j=0;j<n_pole;j++)
			area[i][j]=new_color;
}

void field::draw(int x, int y,int color,int size){
	for(int i=0-size/2;i<=size/2;i++)
		for(int j=0-size/2;j<=size/2;j++)
			if(x+i<n_pole&&y+j<n_pole&&(x+i)>=0&&(y+j)>=0)
				area[x+i][y+j]=color;
}

int field::color(int x,int y){
	return area[x][y];
}

void field::color(int x, int y, int color){
	area[x][y]=color;
}

int** field::get_ar(void){
	return area;
}

int field::n_size(void){
	return n_pole;
}

void field::resize(int n_pole_n){

	delete[] area;

	n_pole=n_pole_n;

	area=new int *[n_pole];
	for(int i=0;i<n_pole;i++)
		area[i]=new int[n_pole];
	clear();
}
