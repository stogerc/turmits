#ifndef GLUT_HPP
#define GLUT_HPP

#include <GL/glut.h>
#include <GL/freeglut_ext.h> //For glutBitmapString();
#include "area.hpp"
#include "turmite.hpp"


#define NTEXT 12 //Text area size


void Reshape(int,int);					//Glut reshape func
void Draw(void);						//Glut redraw func
void timf(int value);					//Glut timer func
void motion(int,int);					//Glut mouse motion func
void special(int,int, int);				//Glut special keys func (cursor keys)
void keyboard(unsigned char,int, int);	//Glut keyb func
void mouse(int, int, int, int);			//Glut mouse func
void menu(int);							//Glut menu func
void createMenu(void);					//Glut create menu func

void numToRGB(int, double&, double&, double&);	//convert 0-15 color to RGB

void glut_cycle(vector<turmite>,field*,int,int,int,int,int,int,int);


#endif
