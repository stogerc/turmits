#include "main.hpp"
using namespace std;
//Global Variables
int Npixels;
int  **area;
	
struct progline{
	string	state;		//Current state
	int		color;		//Current color
	int		Ncolor;		//New color
	int		rotate;
	string	Nstate;		//New state
};
	
vector<progline> prog;
	
int steps;
int Asteps;
unsigned int wassteps;
string qState;
int qLine;
string filename;

int x,y;
int look;

int Timer=0;
int goPerStep=1;

int xmotion, ymotion;
int drawColor=-1;

bool mouseDraw=false;
bool end=false;
bool ispause=0;
bool isShowTurmit=1;

string message;
////////////////////////////////////////////////////


void Reshape(int width, int height){
	glLoadIdentity();
	gluOrtho2D(0, Npixels,-NTEXT, Npixels);
}


void Draw(void){
	int i,j;
	
	if(mouseDraw&&drawColor!=-1){

		j=(xmotion-SPSIZE)/(SQSIZE+SPSIZE);
		i=(ymotion-SPSIZE)/(SQSIZE+SPSIZE);
		if(i<NPOLE&&j<NPOLE&&i-1>=0&&j-1>=0){
			area[i][j]=drawColor;
			area[i-1][j]=drawColor;
			area[i][j-1]=drawColor;
			area[i-1][j-1]=drawColor;
		}
	}
		

	for(i=0;i<goPerStep;i++){
		if((!end)&&(!ispause))
			if(!goTurmit())
				end=true;					
	}
	double r,g,b;
	glClear(GL_COLOR_BUFFER_BIT);	

	glColor3f(1,1,1);
	glRasterPos2f(2,-NTEXT+2);
	char stroka[100];
	sprintf(stroka,
		"Filename:%s Delay: %d.Go per step: %d. \
			Step num: %d. Qrent state: %s %s",filename.c_str(),
		Timer,goPerStep,wassteps,qState.c_str(),message.c_str());
	glutBitmapString(GLUT_BITMAP_HELVETICA_10
			,(const unsigned char*) stroka );
      
	for(i=0;i<NPOLE;i++)
		for(j=0;j<NPOLE;j++){
			numToRGB(area[NPOLE-j-1][i],r,g,b);
			glColor3f(r,g,b);
			glRectf((i*(SQSIZE+SPSIZE)+SPSIZE),
				(j*(SQSIZE+SPSIZE)+SPSIZE),
				(i*(SQSIZE+SPSIZE)+SQSIZE+SPSIZE),
				(j*(SQSIZE+SPSIZE)+SQSIZE+SPSIZE));
		}


	
	if(isShowTurmit){
		i=y;
		j=NPOLE-x-1;
		if(area[(NPOLE-j-1)][i]>8)
			glColor3f(0.0f,0.0f,0.0f);
		else
			glColor3f(1.0f,1.0f,1.0f);
		switch(look){
			case 1:
				glBegin(GL_TRIANGLES);
				glVertex2f(( i*(SQSIZE+SPSIZE)+SPSIZE),
							(j*(SQSIZE+SPSIZE)+SPSIZE));
				glVertex2f(( i*(SQSIZE+SPSIZE)+SPSIZE),
							(j*(SQSIZE+SPSIZE)+SQSIZE+SPSIZE));
				glVertex2f(( i*(SQSIZE+SPSIZE)+SQSIZE+SPSIZE),
							(j*(SQSIZE+SPSIZE)+SQSIZE/2.+SPSIZE));
				glEnd();
			break;
		
			case 0:
				glBegin(GL_TRIANGLES);
				glVertex2f(( i*(SQSIZE+SPSIZE)+SPSIZE),
							(j*(SQSIZE+SPSIZE)+SPSIZE));
				glVertex2f(( i*(SQSIZE+SPSIZE)+SQSIZE+SPSIZE),
							(j*(SQSIZE+SPSIZE)+SPSIZE));
				glVertex2f(( i*(SQSIZE+SPSIZE)+SQSIZE/2.+SPSIZE),
							(j*(SQSIZE+SPSIZE)+SQSIZE+SPSIZE));
				glEnd();
			break;

			case 3:
				glBegin(GL_TRIANGLES);
				glVertex2f(( i*(SQSIZE+SPSIZE)+SQSIZE+SPSIZE),
							(j*(SQSIZE+SPSIZE)+SPSIZE));
				glVertex2f(( i*(SQSIZE+SPSIZE)+SQSIZE+SPSIZE),
							(j*(SQSIZE+SPSIZE)+SQSIZE+SPSIZE));
				glVertex2f(( i*(SQSIZE+SPSIZE)+SPSIZE),
							(j*(SQSIZE+SPSIZE)+SQSIZE/2.+SPSIZE));
				glEnd();

			break;
					
			case 2:
				glBegin(GL_TRIANGLES);
				glVertex2f(( i*(SQSIZE+SPSIZE)+SQSIZE/2.+SPSIZE),
							(j*(SQSIZE+SPSIZE)+SPSIZE));
				glVertex2f(( i*(SQSIZE+SPSIZE)+SQSIZE+SPSIZE),
							(j*(SQSIZE+SPSIZE)+SQSIZE+SPSIZE));
				glVertex2f(( i*(SQSIZE+SPSIZE)+SPSIZE),
							(j*(SQSIZE+SPSIZE)+SQSIZE+SPSIZE));
				glEnd();

			break;
					
		}
	}
			

	glutSwapBuffers();
}

void timf(int value){
	glutPostRedisplay();
	glutTimerFunc(Timer, timf, 0);
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
  		clear();
  	break;
  	
  	
  	case 2:
  		load(filename);
  	break;
  	
  	case 3:
  		ispause=(ispause?false:true);
  	break;
  	  	
  	case 4:
  		to_end();
  	break;

  	case 5:
  		isShowTurmit=!isShowTurmit;
  	break;
	

	case 100:
		drawColor=0;
	break;
	case 101:
		drawColor=1;
	break;  	
	case 102:
		drawColor=2;
	break;
	case 103:
		drawColor=3;
	break;
	case 104:
		drawColor=4;
	break;
	case 105:
		drawColor=5;
	break;
	case 106:
		drawColor=6;
	break;  	
	case 107:
		drawColor=7;
	break;
	case 108:
		drawColor=8;
	break;
	case 109:
		drawColor=9;
	break;
	case 110:
		drawColor=10;
	break;
	case 111:
		drawColor=11;
	break;  	
	case 112:
		drawColor=12;
	break;
	case 113:
		drawColor=13;
	break;
	case 114:
		drawColor=14;
	break;
	case 115:
		drawColor=15;
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



void to_end(void){
	message.clear();
	if(steps>0)
		while(steps>0)
			goTurmit();
	else
		message="Steps not defined";

}

void show_info(void){
	system("clear");
	clog<<"State:"<<qState<<endl;
	clog<<"Color:"<<area[x][y]<<endl;
	clog<<"Wait for:"<<prog[qLine].color<<endl<<endl;
	
	clog<<"Pause between steps:"
	<<Timer<<endl
	<<"Go per step:"
	<<goPerStep<<endl
	<<"Step num:"
	<<wassteps<<endl;
}

void show_prog(void){
	for(unsigned int i=0;i<prog.size();i++)
		cout<<prog[i].state<<" "
			<<prog[i].color<<" "
			<<prog[i].Ncolor<<" "
			<<prog[i].rotate<<" "
			<<prog[i].Nstate<<endl;
}

bool goTurmit(void){

	if(steps>0){
		steps--;
	}else
		if(steps==0){
			cout<<"Шаги закончились";
			if(DBG)
				exit(0);
			return 0;
		}
	wassteps++;
	unsigned int i;
	for(i=0;i<prog.size();i++){
		
		if(((prog[i].state==qState)||prog[i].state=="<*>")	//Заменить на stl
		&&((prog[i].color==area[x][y])||prog[i].color==-1)){
			if(prog[i].Ncolor!=-1)
				area[x][y]=prog[i].Ncolor;

			switch(prog[i].rotate){
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
//			clog<<prog[i].state<<endl;
			if(prog[i].Nstate!="<*>"){
				qState.clear();
				qState=prog[i].Nstate;
			}
			qLine=i;
			break;
		}
	}
	return 1;
}


bool load(string fname){//Переделать
	prog.clear();
	steps=-1;
	Asteps=-1;

	string newstr;
	string stemp;
	
	if(!fname.empty())
		filename=fname;

	ifstream ifs(filename.c_str());
	
	ifs>>newstr;
	
	while(!ifs.eof()){
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
				Asteps=steps;
				while(ifs.get()!='\n');
			}else{
				progline nl;
				nl.state=newstr;
				ifs>>nl.color;
				ifs>>nl.Ncolor;
				ifs>>nl.rotate;
				ifs>>nl.Nstate;
				stemp.clear();
				stemp=nl.Nstate.substr(0,nl.Nstate.find_first_of(";"));
				nl.Nstate.clear();
				nl.Nstate=stemp;
	
				prog.push_back(nl);

				while(ifs.get()!='\n');
				
			}
		}
		newstr.clear();
		ifs>>newstr;
	}
	clear();
	return 1;
}



void go(void){
	switch(look){
		case 0:
	 		x=((x==0)?(NPOLE-1):(x-1));
		break;

		case 1:
	 		y=(y==(NPOLE-1)?0:(y+1));
	 	break;

		case 2:
	 		x=(x==(NPOLE-1)?0:(x+1));
		break;
		
		case 3:
	 		y=((y==0)?(NPOLE-1):(y-1));
	 	break;
	}
}


void initArea(void){
	area=new int *[NPOLE];

	for(int i=0;i<NPOLE;i++)
		area[i]=new int [NPOLE];
}


void clear(void){
	for(int i=0;i<NPOLE;i++)
		for(int j=0;j<NPOLE;j++)
			area[i][j]=0;
	qState=prog[0].state;
	qLine=0;
	x=STARTX;
	y=STARTY;
	look=1;
	steps=Asteps;
	end=false;
	wassteps=0;
}


void left(void){
	look=((look==0)?3:(look-1));
}


void right(void){
	look=((look==3)?0:(look+1));
}


void mouse(int key, int state, int x, int y){
	if(key==3&&state==0)
		Timer=((Timer<10000)?Timer+1:10000);
	if(key==4&&state==0)
		Timer=((Timer>0)?Timer-1:0);
	if(key==0&&state==0){
		mouseDraw=true;
		xmotion=x;
		ymotion=y;
	}
	if(key==0&&state==1)
		mouseDraw=false;
}

void keyboard(unsigned char key,int x, int y){
//	clog<<int(key)<<endl;
	
	switch (key){
		case 32:			//space
			ispause=(ispause?false:true);
		break;
		
		case 113:			//q
			exit(0);
		break;
		
		case 27:			//esc
			exit(0);
		break;
		
		case 114:			//r
			load(filename);
		break;
		
		case 115:			//s
			show_prog();
		break;
		
		case 116:			//t
  			isShowTurmit=!isShowTurmit;
		break;
		
		
		case 13:
			if(!end)
				goTurmit();
		break;
		
		case 92:
			for(int i=0;i<goPerStep;i++){
				if(!end)
					if(!goTurmit())
						end=true;
			}
		break;
		
		
		
	}
}

void special(int key,int x, int y){
//	clog<<key<<endl;
	
	switch (key){
		case 101:
			goPerStep+=100;
		break;
		
		case 103:
			goPerStep=(goPerStep-100>1?goPerStep-100:1);
		break;
	}
//	clog<<goPerStep<<endl;
}


void motion(int x,int y){
	xmotion=x;
	ymotion=y;
	if(mouseDraw&&drawColor!=-1){
		int j=(xmotion-SPSIZE)/(SQSIZE+SPSIZE);
		int i=(ymotion-SPSIZE)/(SQSIZE+SPSIZE);
		if(i<NPOLE&&j<NPOLE&&i-1>=0&&j-1>=0){
			area[i][j]=drawColor;
			area[i-1][j]=drawColor;
			area[i][j-1]=drawColor;
			area[i-1][j-1]=drawColor;
		}
	}
}

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
				ifs>>NPOLE;
			if(newstr=="SQUARE_SIZE")
				ifs>>SQSIZE;
			if(newstr=="GAP_SIZE")
				ifs>>SPSIZE;
			if(newstr=="EXIT_IF_NO_STEPS")
				ifs>>DBG;
			if(newstr=="START_X_POSITION")
				ifs>>STARTX;
			if(newstr=="START_Y_POSITION")
				ifs>>STARTY;
			if(newstr=="GO_PER_STEP")
				ifs>>goPerStep;
			if(newstr=="START_WITH_PAUSE")
				ifs>>ispause;
			if(newstr=="DRAW_COLOR")
				ifs>>drawColor;
			if(newstr=="SHOW_TURMITE")
				ifs>>isShowTurmit;
			if(newstr=="PAUSE_BETWEEN_STEPS")
				ifs>>Timer;
					
			while(ifs.get()!='\n');
				
		}
		newstr.clear();
		ifs>>newstr;
	}
	if(STARTX==-1)
		STARTX=NPOLE/2;
	if(STARTY==-1)
		STARTY=NPOLE/2;
	ifs.close();
	return 1;
}

int main(int Narg,char **arg){

	load_config("config");
	
	Npixels=NPOLE*SQSIZE+(NPOLE+1)*SPSIZE+2;
	
	initArea();
		
	if(Narg>1){
		load(arg[1]);
		Narg--;
		arg++;
	}
	else{
		cerr<<"Use turmit brain file as parametr."<<endl;
		exit(0);
	}
 
 
	glutInit(&Narg, arg);
	glutInitWindowSize(Npixels, Npixels+NTEXT);
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
	
	
	return 0;
}
