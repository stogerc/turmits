#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <GL/glut.h>
#include <GL/freeglut_ext.h> //For glutBitmapString();

#define NTEXT 12 //Text area size

int NPOLE=100;	//NxN area
int SQSIZE=5;
int SPSIZE=1;
bool DBG=0;
int STARTX=NPOLE/2;
int STARTY=NPOLE/2;


void Reshape(int,int);					//Glut reshape func
void Draw(void);						//Glut redraw func
void timf(int value);					//Glut timer func
void motion(int,int);					//Glut mouse motion func
void special(int,int, int);				//Glut special keys func (cursor keys)
void keyboard(unsigned char,int, int);	//Glut keyb func
void mouse(int, int, int, int);			//Glut mouse func
void menu(int);							//Glut menu func

void createMenu(void);					//Glut create menu func

void initArea(void);					//init area dynamic massive
void clear(void);						//clear area, set variables to default


void numToRGB(int, double&, double&, double&);	//convert 0-15 color to RGB
void to_end(void);						//make all steps to end if it exist


bool load(std::string);					//load turmite frome file


void show_prog(void);					//show turmite brain to stdout
void show_info(void);					//show curent state info to stdout

void left(void);						//move turmite left
void right(void);						//move turmite right
void go(void);							//go turmite forward

bool goTurmit(void);					//make one step


int load_config(std::string);			//load setings from config


#endif
