/*
Fl_Help_dialog
Fl_menu_button
Fl_color_chooser
Fl_show_colormap
*/
#include "fltk.hpp"
#include <iostream>
using namespace std;

Fl_Input *input;
Fl_Slider *slider;
Fl_Slider *slider_steps;
Fl_Menu_Button *rmbutton;

double timer=1;

int n_pixels;
bool is_pause=0;
int draw_color=1;
bool draw=false;
bool drag=false;
int drag_x;
int drag_y;

int sqr_size=1;
int gap_size=1;
int n_field=100;
int go_per_step=1;
bool is_show_turmite=1;
int start_x=0;
int start_y=0;


int draw_size=1;

field *area;
vector<turmite> turmite_v;
vector<basefield*> basefield_v;
	vector<turfield> turfield_fltk_v;
	vector<rulefield> rulefield_fltk_v;
	

void quit_cb(Fl_Widget*, void*) {
	exit(0);
}

void Reshape(int width, int height){
	glLoadIdentity();
	gluOrtho2D(0, n_pixels,0, n_pixels);
}


void Draw(void){
	int i,j;

	if(!is_pause){
		for(j=0;j<turmite_v.size();j++)
			turmite_v[j].goTurmit(go_per_step);

		for(j=0;j<basefield_v.size();j++)
			basefield_v[j]->step(go_per_step);
	}

	double r,g,b;
	glClear(GL_COLOR_BUFFER_BIT);	


	for(i=0;i<n_field;i++)
		for(j=0;j<n_field;j++){
			numToRGB((*area).color(n_field-j-1,i),r,g,b);
			glColor3f(r,g,b);
			glRectf((i*(sqr_size+gap_size)+gap_size),
				(j*(sqr_size+gap_size)+gap_size),
				(i*(sqr_size+gap_size)+sqr_size+gap_size),
				(j*(sqr_size+gap_size)+sqr_size+gap_size));
		}

	int x,y;


	if(is_show_turmite){
		for(int k=0;k<turmite_v.size();k++){
			turmite_v[k].get_x_y(x,y);
			i=y;
			j=n_field-x-1;
			if((*area).color((n_field-j-1),i)>8)
				glColor3f(0.0f,0.0f,0.0f);
			else
				glColor3f(1.0f,1.0f,1.0f);

			switch(turmite_v[k].get_look()){
				case 1:
					glBegin(GL_TRIANGLES);
					glVertex2f(( i*(sqr_size+gap_size)
									+gap_size),
								(j*(sqr_size+gap_size)+gap_size));
					glVertex2f(( i*(sqr_size+gap_size)
									+gap_size),
								(j*(sqr_size+gap_size)
									+sqr_size+gap_size));
					glVertex2f(( i*(sqr_size+gap_size)
									+sqr_size+gap_size),
								(j*(sqr_size+gap_size)
									+sqr_size/2.+gap_size));
					glEnd();
				break;
		
				case 0:
					glBegin(GL_TRIANGLES);
					glVertex2f(( i*(sqr_size+gap_size)+gap_size),
								(j*(sqr_size+gap_size)+gap_size));
					glVertex2f(( i*(sqr_size+gap_size)
									+sqr_size+gap_size),
								(j*(sqr_size+gap_size)+gap_size));
					glVertex2f(( i*(sqr_size+gap_size)
									+sqr_size/2.+gap_size),
								(j*(sqr_size+gap_size)
									+sqr_size+gap_size));
					glEnd();
				break;

				case 3:
					glBegin(GL_TRIANGLES);
					glVertex2f(( i*(sqr_size+gap_size)
									+sqr_size+gap_size),
								(j*(sqr_size+gap_size)+gap_size));
					glVertex2f(( i*(sqr_size+gap_size)
									+sqr_size+gap_size),
								(j*(sqr_size+gap_size)
									+sqr_size+gap_size));
					glVertex2f(( i*(sqr_size+gap_size)+gap_size),
								(j*(sqr_size+gap_size)
									+sqr_size/2.+gap_size));
					glEnd();

				break;
					
				case 2:
					glBegin(GL_TRIANGLES);
					glVertex2f(( i*(sqr_size+gap_size)
									+sqr_size/2.+gap_size),
								(j*(sqr_size+gap_size)
									+gap_size));
					
					glVertex2f(( i*(sqr_size+gap_size)
									+sqr_size+gap_size),
								(j*(sqr_size+gap_size)
									+sqr_size+gap_size));
									
					glVertex2f(( i*(sqr_size+gap_size)
									+gap_size),
								(j*(sqr_size+gap_size)
									+sqr_size+gap_size));
					glEnd();

				break;
					
			}
		}
	}
			

	glutSwapBuffers();
}

void numToRGB(int num, double &r, double &g, double &b){

	switch(num){

		case 0:
			r=0;
			g=0;
			b=0;
		break;
	
		case 1:
			r=0;
			g=0;
			b=10/16.;
		break;
		
		case 2:
			r=0;
			g=10/16.;
			b=0;
		break;
		
		case 3:
			r=0;
			g=10/16.;
			b=10/16.;
		break;
		
		case 4:
			r=10/16.;
			g=0;
			b=0;
		break;
		
		case 5:
			r=10/16.;
			g=0;
			b=10/16.;
		break;
			
		case 6:
			r=10/16.;
			g=5/16.;
			b=0;
		break;
			
		case 7:
			r=10/16.;
			g=10/16.;
			b=10/16.;
		break;
		
		case 8:
			r=5/16.;
			g=5/16.;
			b=5/16.;
		break;
		
		case 9:
			r=5/16.;
			g=5/16.;
			b=1;
		break;
		
		case 10:
			r=5/16.;
			g=1;
			b=5/16.;
		break;
	
		case 11:
			r=5/16.;
			g=1;
			b=1;
		break;
		
		case 12:
			r=1;
			g=5/16.;
			b=5/16.;
		break;
		
		case 13:
			r=1;
			g=5/16.;
			b=1;
		break;
		
		case 14:
			r=1;
			g=1;
			b=5/16.;
		break;
		
		case 15:
			r=1;
			g=1;
			b=1;
		break;
		
		default:
			r=int(num/100);
			g=int((num/10)%10);
			b=int(num%10);
			r=r/9.;
			g=g/9.;
			b=b/9.;
		break;
	}
}


//void menu(int value){
//  switch(value){
//  
//  	case 0:
//  		exit(0);
//  	break;
//  	
//  	case 1:

//  	break;
//  	
//  	
//  	case 2:
//  		//(*pturm).load(filename);
//  	break;
//  	
//  	case 3:
//  		is_pause=(is_pause?false:true);
//  	break;
//  	  	
//  	case 4:
//  		//(*pturm).to_end();
//  	break;

//  	case 5:
//  		is_show_turmite=!is_show_turmite;
//  	break;
//	

//	case 100:
//		draw_color=0;
//	break;
//	case 101:
//		draw_color=1;
//	break;  	
//	case 102:
//		draw_color=2;
//	break;
//	case 103:
//		draw_color=3;
//	break;
//	case 104:
//		draw_color=4;
//	break;
//	case 105:
//		draw_color=5;
//	break;
//	case 106:
//		draw_color=6;
//	break;  	
//	case 107:
//		draw_color=7;
//	break;
//	case 108:
//		draw_color=8;
//	break;
//	case 109:
//		draw_color=9;
//	break;
//	case 110:
//		draw_color=10;
//	break;
//	case 111:
//		draw_color=11;
//	break;  	
//	case 112:
//		draw_color=12;
//	break;
//	case 113:
//		draw_color=13;
//	break;
//	case 114:
//		draw_color=14;
//	break;
//	case 115:
//		draw_color=15;
//	break;
//		


//  	
//  }
//  
//  glutPostRedisplay();
//}

//void createMenu(void){
//	int collors=glutCreateMenu(menu);
//	glutAddMenuEntry("Black", 100);
//	glutAddMenuEntry("Blue", 101);
//	glutAddMenuEntry("Green", 102);
//	glutAddMenuEntry("Cyan", 103);
//	glutAddMenuEntry("Red", 104);
//	glutAddMenuEntry("Magenta", 105);
//	glutAddMenuEntry("Brown", 106);
//	glutAddMenuEntry("Light gray", 107);
//	glutAddMenuEntry("Dark gray", 108);
//	glutAddMenuEntry("Bright blue", 109);
//	glutAddMenuEntry("Bright green", 110);
//	glutAddMenuEntry("Bright cyan", 111);
//	glutAddMenuEntry("Bright red", 112);
//	glutAddMenuEntry("Bright magenta", 113);
//	glutAddMenuEntry("Bright yellow", 114);
//	glutAddMenuEntry("White", 115);
//	
//	int submenu=glutCreateMenu(menu);
//	glutAddMenuEntry("Sand", 114);
//	glutAddMenuEntry("Eraser", 100);
//	glutAddMenuEntry("Wall", 103);
//	glutAddMenuEntry("Flame", 104);
//	glutAddMenuEntry("Wood", 106);
//	
//	glutCreateMenu(menu);

//	glutAddMenuEntry("Quit (q)", 0);
//	glutAddMenuEntry("Reset", 1);
//	glutAddMenuEntry("Reload (r)", 2);
//	glutAddMenuEntry("Play/Pause (space)", 3);
//	glutAddMenuEntry("To end", 4);
//	glutAddMenuEntry("Show/Hide turmit (t)", 5);
//	
//	glutAddSubMenu("Set tool",submenu);
//  	glutAddSubMenu("Set color",collors);
//  
//	glutAttachMenu(GLUT_RIGHT_BUTTON);


//}


////////////////////////////////////////////////////////

void mouse(int key, int state, int x, int y){
	if(state==0){
		switch(key){
			case 3:
				timer=((timer<2980)?exp(log(timer)+1):2980);
				slider->value(log(timer));
			break;
			
			case 4:
				timer=((timer>1)?exp(log(timer)-1):1);
				slider->value(log(timer));
			break;
			
			case 0:{
				int j=(x-gap_size)/(sqr_size+gap_size);
				int i=(y-gap_size)/(sqr_size+gap_size);
				(*area).draw(i,j,draw_color,draw_size);
				draw=true;
			}break;
			
			case 2:{
				int j=(x-gap_size)/(sqr_size+gap_size);
				int i=(y-gap_size)/(sqr_size+gap_size);
				(*area).draw(i,j,0,draw_size);
			}break;
			
			case 1:{
				drag=true;
				drag_y=(x-gap_size)/(sqr_size+gap_size);
				drag_x=(y-gap_size)/(sqr_size+gap_size);
			}break;
			
			
			default:
				
			break;
		}
	}else{
		draw=false;
		drag=false;
	}
}

void keyboard(unsigned char key,int x, int y){
//	clog<<int(key)<<endl;
	
	switch (key){
		case 32:			//space
			is_pause=!is_pause;
		break;
		
		case 113:			//q
			exit(0);
		break;
		
		case 27:			//esc
			exit(0);
		break;
		
		case 114:			//r
			for(int j=0;j<turmite_v.size();j++){
				turmite_v[j].load();
				turmite_v[j].reset();
			}
			(*area).clear();
		break;
		
		case 116:			//t
  			is_show_turmite=!is_show_turmite;
		break;
		
		
		case 13:
			for(int j=0;j<turmite_v.size();j++)
				turmite_v[j].goTurmit();
			for(int j=0;j<basefield_v.size();j++)
				basefield_v[j]->step(go_per_step);
			
		break;
		
		case 92:
			for(int j=0;j<turmite_v.size();j++)
				turmite_v[j].goTurmit(go_per_step);
			for(int j=0;j<basefield_v.size();j++)
				basefield_v[j]->step();
		break;
	}
	if(key>=49&&key<=57)
		draw_size=int(key)-48;
}

void special(int key,int x, int y){
//	clog<<key<<endl;
	
	switch (key){
		case 65362:
			go_per_step=exp(log(go_per_step)+1);
			slider_steps->value(log(go_per_step));
		break;
		
		case 65364:
			go_per_step=exp(log(go_per_step)-1);
			slider_steps->value(log(go_per_step));
		break;
		
		case 65361:
			timer=((timer>1)?timer-1:1);
			slider->value(log(timer));
		break;
		
		case 65363:
			timer=((timer<2980)?timer+1:2980);
			slider->value(log(timer));
		break;
		
	}
//	clog<<go_per_step<<endl;
}


void motion(int x,int y){
//	clog<<x<<endl<<y<<endl<<endl;
	if(draw_color!=-1&&draw){
		int j=(x-gap_size)/(sqr_size+gap_size);
		int i=(y-gap_size)/(sqr_size+gap_size);
		if(i<n_field&&j<n_field&&i-1>=0&&j-1>=0){
			(*area).draw(i,j,draw_color,draw_size);
		}
	}
	if(drag){
		int **locarea=area->get_ar();
		int ny=(x-gap_size)/(sqr_size+gap_size);
		int nx=(y-gap_size)/(sqr_size+gap_size);
//		clog<<drag_x<<endl<<drag_y<<endl;
//		clog<<nx<<endl<<ny<<endl<<endl;
		if(drag_x!=nx||drag_y!=ny){
			int n_pole=area->n_size();
			int ifirst,ilast,iplus;
			int jfirst,jlast,jplus;
			
			if(nx-drag_x<=0){
				ifirst=0;
				ilast=n_pole;
				iplus=1;
			}else{
				ifirst=n_pole-1;
				ilast=-1;
				iplus=-1;
			}
			if(ny-drag_y<=0){
				jfirst=0;
				jlast=n_pole;
				jplus=1;
			}else{
				jfirst=n_pole-1;
				jlast=-1;
				jplus=-1;
			}
			
			for(int i=ifirst;i!=ilast;i+=iplus){
				for(int j=jfirst;j!=jlast;j+=jplus){
					int dx=i-nx+drag_x;
					int dy=j-ny+drag_y;

					if(dx<0||dx>(n_pole-1)||dy<0||dy>(n_pole-1)){
						locarea[i][j]=0;
					}else{
						locarea[i][j]=locarea[dx][dy];
					//	clog<<dx<<endl<<dy<<endl<<endl;
					}

				}
			}
			
			
			drag_x=nx;
			drag_y=ny;
		}
	}
	//glutPostRedisplay();
}

void timer_redraw(void*) {
	glutPostRedisplay();
	Fl::repeat_timeout(double(1./((timer==0)?1:timer)),timer_redraw);
}

void button_color(Fl_Widget *w,void*){
	Fl_Button *b=(Fl_Button*)w;
	draw_color=atoi(b->label());
	input->value(b->label());
}

void input_cb(Fl_Widget *w,void*){
	Fl_Input *in=(Fl_Input*)w;
	int new_in=atoi(in->value());
	if(new_in>99&&new_in<1000){
		draw_color=new_in;
	}
}

void slider_cb(Fl_Widget *w,void*){
	Fl_Slider *sl=(Fl_Slider*)w;
	timer=exp(sl->value());
}

void slider_steps_cb(Fl_Widget *w,void*){
	Fl_Slider *sl=(Fl_Slider*)w;
	go_per_step=exp(sl->value());
}

void button_cb(Fl_Widget *w,void*){
	Fl_Button *b=(Fl_Button*)w;
	if(!strcmp(b->label(),"reload")){
		for(int j=0;j<turmite_v.size();j++){
				turmite_v[j].load();
				turmite_v[j].reset();
		}
		for(int j=0;j<basefield_v.size();j++){
				basefield_v[j]->load();
		}
		(*area).clear();
	}
	if(!strcmp(b->label(),"reset")){
		for(int j=0;j<turmite_v.size();j++){
				turmite_v[j].reset();
		}
		(*area).clear();
	}
	if(!strcmp(b->label(),"clear")){
		(*area).clear();
	}
	if(!strcmp(b->label(),"quit")){
		exit(0);
	}
	if(!strcmp(b->label(),"pause")){
		is_pause=true;
		b->label("play");
	}else{
		if(!strcmp(b->label(),"play")){
			is_pause=false;
			b->label("pause");
		}
	}
	if(!strcmp(b->label(),"step")){
		for(int j=0;j<turmite_v.size();j++)
			turmite_v[j].goTurmit();
		for(int j=0;j<basefield_v.size();j++)
			basefield_v[j]->step(go_per_step);
	}
	if(!strcmp(b->label(),"x steps")){
		for(int j=0;j<turmite_v.size();j++)
			turmite_v[j].goTurmit(go_per_step);
		for(int j=0;j<basefield_v.size();j++)
			basefield_v[j]->step();
	}
	
}

void add_turmite_cb(Fl_Widget *w,void*){
	Fl_Menu_Button *b=(Fl_Menu_Button*)w;
	Fl_File_Chooser chooser(".","*",Fl_File_Chooser::MULTI,"Open file");
	chooser.show();
	while(chooser.shown()){
		Fl::wait();
	}

	if(chooser.value()==NULL){
		return;
	}

	
	switch(b->value()){
		case 0:
			for(int t=1;t<=chooser.count();t++){
				turmite myturm(area->get_ar(),n_field,chooser.value(t),
				start_x,start_y);
				turmite_v.push_back(myturm);
			}
		break;
			
		case 1:
			for(int t=1;t<=chooser.count();t++){
				turfield mytfield(area->get_ar(),n_field,chooser.value(t));
				turfield_fltk_v.push_back(mytfield);
				basefield_v.push_back((basefield*)&turfield_fltk_v[turfield_fltk_v.size()-1]);
			}
		break;
		
		case 2:
			for(int t=1;t<=chooser.count();t++){
				rulefield myrufield(area->get_ar(),n_field,chooser.value(t));
				rulefield_fltk_v.push_back(myrufield);
				basefield_v.push_back((basefield*)&rulefield_fltk_v[rulefield_fltk_v.size()-1]);
			}
		break;
	}
	rmbutton_re();

}

void timf(int value){
	glutPostRedisplay();
	glutTimerFunc(((timer==0)?1:timer), timf, 0);
}

void rmbutton_cb(Fl_Widget *w,void*){
	Fl_Menu_Button *b=(Fl_Menu_Button*)w;
	int num=b->value();
	if(num>=turmite_v.size()){
		basefield_v.erase(basefield_v.begin()+num-turmite_v.size());
	}else{
		turmite_v.erase(turmite_v.begin()+num);
	}
	rmbutton_re();
}

int n_cifr(int chislo){
	return chislo/10?1+n_cifr(chislo/10):1;
}

string dec2str(int dec){
	string mystr;
	int n_cifr_r=n_cifr(dec);
	mystr.resize(n_cifr_r);
	for(int i=0;i<n_cifr_r;i++){
		mystr[i]=char((dec/int(pow(10,n_cifr_r-i-1)))%10+48);
	}


	return mystr;
}

void rmbutton_re(void){
	rmbutton->clear();
	
	for(int j=0;j<turmite_v.size();j++){

		string punkt="("+dec2str(j+1)+") "+turmite_v[j].get_filename();
		rmbutton->add(punkt.c_str(),0,rmbutton_cb);
	}
	for(int j=0;j<basefield_v.size();j++){
		string punkt="("+dec2str(turmite_v.size()+j+1)+") "+basefield_v[j]->get_filename();
		rmbutton->add(punkt.c_str(),0,rmbutton_cb);
	}
}

void calc_cb(Fl_Widget *w,void*){
	vector<int> win;
	for(int i=0;i<16;i++)
		win.push_back(0);
	for(int i=0;i<n_field;i++)
		for(int j=0;j<n_field;j++)
			if(area->color(i,j)<16)
				win[area->color(i,j)]++;
	string message;
	for(int i=0;i<16;i++)
		message+=" "+dec2str(win[i]);
	clog<<message<<endl;
			
}

void fltk_cycle(vector<basefield*> opt_basefield_v,
				int opt_start_x,int opt_start_y,
				vector<turmite> old_turmite_v,field *myar,int opt_sqr_size,
				int opt_gap_size,int opt_n_field,int opt_go_per_step,
				int opt_draw_color,int opt_is_show_turmite,int opt_timer){

	int argc=1;
	char **argv=new char*;
	*argv=new char;

	sqr_size=opt_sqr_size;
	gap_size=opt_gap_size;
	n_field=opt_n_field;
	go_per_step=opt_go_per_step;
	draw_color=opt_draw_color;
	is_show_turmite=opt_is_show_turmite;
	timer=opt_timer;
	turmite_v=old_turmite_v;
	basefield_v=opt_basefield_v;
	start_x=opt_start_x;
	start_y=opt_start_y;

	area=myar;
	
	n_pixels=n_field*sqr_size+(n_field+1)*gap_size+2;
	
	Fl_Window win(n_pixels,n_pixels+60, "turmits");

	Fl_Menu_Bar menubar(0,0,40,20);
	menubar.add("File/Quit", 0, quit_cb);

	Fl_Button  *b;
	int x=40;
	int y=0;
	int bsize=20;
	int plus_x=20;
	int plus_y=0;
	b=new Fl_Button(x,y,bsize,bsize,"0");x+=plus_x;y+=plus_y;
		b->color(fl_rgb_color(0,0,0));b->callback(button_color);
		b->labeltype(FL_NO_LABEL);
	b=new Fl_Button(x,y,bsize,bsize,"1");x+=plus_x;y+=plus_y;
		b->color(fl_rgb_color(0,0,170));b->callback(button_color);
		b->labeltype(FL_NO_LABEL);
	b=new Fl_Button(x,y,bsize,bsize,"2");x+=plus_x;y+=plus_y;
		b->color(fl_rgb_color(0,170,0));b->callback(button_color);
		b->labeltype(FL_NO_LABEL);
	b=new Fl_Button(x,y,bsize,bsize,"3");x+=plus_x;y+=plus_y;
		b->color(fl_rgb_color(0,170,170));b->callback(button_color);
		b->labeltype(FL_NO_LABEL);
	b=new Fl_Button(x,y,bsize,bsize,"4");x+=plus_x;y+=plus_y;
		b->color(fl_rgb_color(170,0,0));b->callback(button_color);
		b->labeltype(FL_NO_LABEL);
	b=new Fl_Button(x,y,bsize,bsize,"5");x+=plus_x;y+=plus_y;
		b->color(fl_rgb_color(170,0,170));b->callback(button_color);
		b->labeltype(FL_NO_LABEL);
	b=new Fl_Button(x,y,bsize,bsize,"6");x+=plus_x;y+=plus_y;
		b->color(fl_rgb_color(170,85,0));b->callback(button_color);
		b->labeltype(FL_NO_LABEL);
	b=new Fl_Button(x,y,bsize,bsize,"7");x+=plus_x;y+=plus_y;
		b->color(fl_rgb_color(170,170,170));b->callback(button_color);
		b->labeltype(FL_NO_LABEL);
	b=new Fl_Button(x,y,bsize,bsize,"8");x+=plus_x;y+=plus_y;
		b->color(fl_rgb_color(85,85,85));b->callback(button_color);
		b->labeltype(FL_NO_LABEL);
	b=new Fl_Button(x,y,bsize,bsize,"9");x+=plus_x;y+=plus_y;
		b->color(fl_rgb_color(85,85,255));b->callback(button_color);
		b->labeltype(FL_NO_LABEL);
	b=new Fl_Button(x,y,bsize,bsize,"10");x+=plus_x;y+=plus_y;
		b->color(fl_rgb_color(85,255,85));b->callback(button_color);
		b->labeltype(FL_NO_LABEL);
	b=new Fl_Button(x,y,bsize,bsize,"11");x+=plus_x;y+=plus_y;
		b->color(fl_rgb_color(85,255,255));b->callback(button_color);
		b->labeltype(FL_NO_LABEL);
	b=new Fl_Button(x,y,bsize,bsize,"12");x+=plus_x;y+=plus_y;
		b->color(fl_rgb_color(255,85,85));b->callback(button_color);
		b->labeltype(FL_NO_LABEL);
	b=new Fl_Button(x,y,bsize,bsize,"13");x+=plus_x;y+=plus_y;
		b->color(fl_rgb_color(255,85,255));b->callback(button_color);
		b->labeltype(FL_NO_LABEL);
	b=new Fl_Button(x,y,bsize,bsize,"14");x+=plus_x;y+=plus_y;
		b->color(fl_rgb_color(255,255,85));b->callback(button_color);
		b->labeltype(FL_NO_LABEL);
	b=new Fl_Button(x,y,bsize,bsize,"15");x+=plus_x;y+=plus_y;
		b->color(fl_rgb_color(255,255,255));b->callback(button_color);
		b->labeltype(FL_NO_LABEL);
	

	input=new Fl_Input(410,0,40,20,"color:");
	input->callback(input_cb);
	
	slider=new Fl_Slider(0,n_pixels+20,100,20,"redraw speed");
	slider->labeltype(FL_NORMAL_LABEL);
	slider->type(1);
	slider->callback(slider_cb);
	slider->bounds(0,8);
	slider->value(log(opt_timer));//Грубо
	
	slider_steps=new Fl_Slider(110,n_pixels+20,100,20,
	"steps/redraw");
	slider_steps->labeltype(FL_NORMAL_LABEL);
	slider_steps->type(1);
	slider_steps->callback(slider_steps_cb);
	slider_steps->bounds(0,10);
	slider_steps->value(14*opt_go_per_step/16384.);//Грубо
	
	
	
	b=new Fl_Button(220,n_pixels+20,70,bsize,"reload");
	b->callback(button_cb);
	b=new Fl_Button(220,n_pixels+40,70,bsize,"reset");
	b->callback(button_cb);
	b=new Fl_Button(290,n_pixels+20,70,bsize,"clear");
	b->callback(button_cb);
	b=new Fl_Button(500,n_pixels+40,70,bsize,"quit");
	b->callback(button_cb);
	b=new Fl_Button(290,n_pixels+40,70,bsize,"pause");
	b->callback(button_cb);
	b=new Fl_Button(360,n_pixels+20,70,bsize,"step");
	b->callback(button_cb);
	b=new Fl_Button(360,n_pixels+40,70,bsize,"x steps");
	b->callback(button_cb);
	b=new Fl_Button(500,n_pixels+20,70,bsize,"calc");
	b->callback(calc_cb);
	
	
	
	Fl_Menu_Button mybutton(430,n_pixels+20,70,bsize,"add");
	mybutton.add("turmite",0,add_turmite_cb);
	mybutton.add("cellular automata",0,add_turmite_cb);
	mybutton.add("elementary cellular automata",0,add_turmite_cb);
	
	rmbutton=new Fl_Menu_Button(430,n_pixels+40,70,bsize,"rm");
	rmbutton_re();
	
	win.resizable(win);
	Fl::repeat_timeout(1.0/10000.,timer_redraw);

	win.show(argc, argv);

	win.begin();
	glutInitWindowSize(n_pixels,n_pixels);
	glutInitWindowPosition(0,20);

	glutCreateWindow("Turmits");

	glutReshapeFunc(Reshape);
	glutDisplayFunc(Draw);
	glutMouseFunc(mouse);

   	glutMotionFunc(motion);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);

//	glutTimerFunc(0, timf, 0);

	win.end();

	Fl::run();
}
