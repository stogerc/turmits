#include "glut.hpp"

int timer=10;

int n_pixels;
bool is_pause=0;
int draw_color=-1;


int sqr_size=1;
int gap_size=1;
int n_field=100;
int go_per_step=10;
bool is_show_turmite=1;


int draw_size=1;

field *area;
vector<turmite> turmite_v;


void Reshape(int width, int height){
	glLoadIdentity();
	gluOrtho2D(0, n_pixels,-NTEXT, n_pixels);
}


void Draw(void){
	int i,j;

	for(i=0;i<go_per_step;i++){
		if(!is_pause)
			for(j=0;j<turmite_v.size();j++)
				turmite_v[j].goTurmit();					
	}

	double r,g,b;
	glClear(GL_COLOR_BUFFER_BIT);	

	glColor3f(1,1,1);
	glRasterPos2f(2,-NTEXT+2);
	char stroka[100];
	sprintf(stroka,
		"Delay: %d.Go per step: %d.",
				timer,go_per_step);
				
	glutBitmapString(GLUT_BITMAP_HELVETICA_10
			,(const unsigned char*) stroka );

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
			//clog<<x<<" "<<y<<endl;
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

void timf(int value){
	glutPostRedisplay();
	glutTimerFunc(timer, timf, 0);
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
			r=0;
			g=0;
			b=0;
		break;
			
	}
}


void menu(int value){
  switch(value){
  
  	case 0:
  		exit(0);
  	break;
  	
  	case 1:

  	break;
  	
  	
  	case 2:
  		//(*pturm).load(filename);
  	break;
  	
  	case 3:
  		is_pause=(is_pause?false:true);
  	break;
  	  	
  	case 4:
  		//(*pturm).to_end();
  	break;

  	case 5:
  		is_show_turmite=!is_show_turmite;
  	break;
	

	case 100:
		draw_color=0;
	break;
	case 101:
		draw_color=1;
	break;  	
	case 102:
		draw_color=2;
	break;
	case 103:
		draw_color=3;
	break;
	case 104:
		draw_color=4;
	break;
	case 105:
		draw_color=5;
	break;
	case 106:
		draw_color=6;
	break;  	
	case 107:
		draw_color=7;
	break;
	case 108:
		draw_color=8;
	break;
	case 109:
		draw_color=9;
	break;
	case 110:
		draw_color=10;
	break;
	case 111:
		draw_color=11;
	break;  	
	case 112:
		draw_color=12;
	break;
	case 113:
		draw_color=13;
	break;
	case 114:
		draw_color=14;
	break;
	case 115:
		draw_color=15;
	break;
		


  	
  }
  
  glutPostRedisplay();
}

void createMenu(void){
	int collors=glutCreateMenu(menu);
	glutAddMenuEntry("Black", 100);
	glutAddMenuEntry("Blue", 101);
	glutAddMenuEntry("Green", 102);
	glutAddMenuEntry("Cyan", 103);
	glutAddMenuEntry("Red", 104);
	glutAddMenuEntry("Magenta", 105);
	glutAddMenuEntry("Brown", 106);
	glutAddMenuEntry("Light gray", 107);
	glutAddMenuEntry("Dark gray", 108);
	glutAddMenuEntry("Bright blue", 109);
	glutAddMenuEntry("Bright green", 110);
	glutAddMenuEntry("Bright cyan", 111);
	glutAddMenuEntry("Bright red", 112);
	glutAddMenuEntry("Bright magenta", 113);
	glutAddMenuEntry("Bright yellow", 114);
	glutAddMenuEntry("White", 115);
	
	int submenu=glutCreateMenu(menu);
	glutAddMenuEntry("Sand", 114);
	glutAddMenuEntry("Eraser", 100);
	glutAddMenuEntry("Wall", 103);
	glutAddMenuEntry("Flame", 104);
	glutAddMenuEntry("Wood", 106);
	
	glutCreateMenu(menu);

	glutAddMenuEntry("Quit (q)", 0);
	glutAddMenuEntry("Reset", 1);
	glutAddMenuEntry("Reload (r)", 2);
	glutAddMenuEntry("Play/Pause (space)", 3);
	glutAddMenuEntry("To end", 4);
	glutAddMenuEntry("Show/Hide turmit (t)", 5);
	
	glutAddSubMenu("Set tool",submenu);
  	glutAddSubMenu("Set color",collors);
  
	glutAttachMenu(GLUT_RIGHT_BUTTON);


}


////////////////////////////////////////////////////////

void mouse(int key, int state, int x, int y){
	if(key==3&&state==0)
		timer=((timer<10000)?timer+1:10000);
	if(key==4&&state==0)
		timer=((timer>0)?timer-1:0);
	if(key==0&&state==0){
		int j=(x-gap_size)/(sqr_size+gap_size);
		int i=(y-gap_size)/(sqr_size+gap_size);
		(*area).draw(i,j,draw_color,draw_size);
	}
}

void keyboard(unsigned char key,int x, int y){
//	clog<<int(key)<<endl;
	
	switch (key){
		case 32:			//space
			is_pause=(is_pause?false:true);
		break;
		
		case 113:			//q
			exit(0);
		break;
		
		case 27:			//esc
			exit(0);
		break;
		
		case 114:			//r
		//	(*pturm).load(filename);
		break;
		
		case 115:			//s
		//	(*pturm).show_brain();
		break;
		
		case 116:			//t
  			is_show_turmite=!is_show_turmite;
		break;
		
		
		case 13:
//			if(!end)
//				(*pturm).goTurmit();
		break;
		
		case 92:
//			for(int i=0;i<go_per_step;i++){
//				if(!end)
//					if(!(*pturm).goTurmit())
//						end=true;
//			}
		break;
	}
	if(key>=49&&key<=57)
		draw_size=int(key)-48;
}

void special(int key,int x, int y){
//	clog<<key<<endl;
	
	switch (key){
		case 101:
			go_per_step+=100;
		break;
		
		case 103:
			go_per_step=(go_per_step-100>1?go_per_step-100:1);
		break;
	}
//	clog<<go_per_step<<endl;
}


void motion(int x,int y){
	if(draw_color!=-1){
		int j=(x-gap_size)/(sqr_size+gap_size);
		int i=(y-gap_size)/(sqr_size+gap_size);
		if(i<n_field&&j<n_field&&i-1>=0&&j-1>=0){
			(*area).draw(i,j,draw_color,draw_size);
		}
	}
}

void glut_cycle(vector<turmite> old_turmite_v,field *myar,int opt_sqr_size,
				int opt_gap_size,int opt_n_field,int opt_go_per_step,
				int opt_draw_color,int opt_is_show_turmite,int opt_timer){
	
	int Narg=1;
	char **arg=new char*;

	sqr_size=opt_sqr_size;
	gap_size=opt_gap_size;
	n_field=opt_n_field;
	go_per_step=opt_go_per_step;
	draw_color=opt_draw_color;
	is_show_turmite=opt_is_show_turmite;
	timer=opt_timer;
	turmite_v=old_turmite_v;
	
	area=myar;
	
	n_pixels=n_field*sqr_size+(n_field+1)*gap_size+2;

	glutInit(&Narg, arg);

	glutInitWindowSize(n_pixels, n_pixels+NTEXT);
	(void)glutCreateWindow("turmits");
	createMenu();
	glutReshapeFunc(Reshape);
	glutDisplayFunc(Draw);
	glutTimerFunc(0, timf, 0);
	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);
	glutMotionFunc(motion);

	glutMainLoop();
}
/*
glut_cycle parametrs:

go_per_step




*/
