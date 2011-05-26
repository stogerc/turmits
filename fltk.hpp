#ifndef FLTK_HPP
#define FLTK_HPP

#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_File_Chooser.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Slider.H>
#include <FL/glut.H>
#include <FL/gl.h>
#include <FL/glu.h>
#include <FL/Fl_Button.H>
#include <FL/Fl_Menu_Button.H>
#include <FL/fl_ask.H>



#include "turmite.hpp"
#include "area.hpp"
#include "turfield.hpp"
#include "basefield.hpp"
#include "rulefield.hpp"

#define BOX_TYPE FL_THIN_UP_BOX
#define NTEXT 12 //Text area size

void fltk_cycle(vector<basefield*>,int,int,
				vector<turmite>,field*,int,int,int,int,int,int,int);

void Reshape(int,int);					//Glut reshape func
void Draw(void);						//Glut redraw func
void timf(int value);					//Glut timer func
void motion(int,int);					//Glut mouse motion func
void special(int,int, int);				//Glut special keys func (cursor keys)
void keyboard(unsigned char,int, int);	//Glut keyb func
void mouse(int, int, int, int);			//Glut mouse func
void menu(int);							//Glut menu func
void createMenu(void);					//Glut create menu func
void rmbutton_re(void);

void numToRGB(int, double&, double&, double&);	//convert 0-15 color to RGB


#endif
