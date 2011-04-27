/*
	+ Количество сделанных шагов
	+ Режим совместимости с грёбанной виндовой версией
	+ Доработать goTurmit не надо
	- Добавить makefile
	+ Много времени на отрисовку клеток
	+ Смешать режим нескольких шагов и обычный
	+ Вывод текста в обычном режиме
*/
#include "main.hpp"
using namespace std;

int Npixels=NPOLE*SQSIZE+(NPOLE+1)*SPSIZE+2;


	
///////////////////////////////////////////////////////////

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
	
	int drawColor=0;
	
	int x,y;
	int look;
	bool end=false;
	bool ispause=true;
	int Timer=0;
	int goPerStep=1;

////////////////////////////////////////////////////


void Reshape(int width, int height){
	glLoadIdentity();
	gluOrtho2D(0, Npixels,0, Npixels+10);
}



void Draw(void){
	int i,j;

	for(int i=0;i<goPerStep;i++){
		if((!end)&&ispause)
			if(!goTurmit())
				end=true;					
	}
	double r,g,b;
	glClear(GL_COLOR_BUFFER_BIT);	

	glColor3f(1,1,1);
	glRasterPos2f(SPSIZE+1,Npixels-1);
	char stroka[100];
	sprintf(stroka,
		"Pause between steps: %d ms.Go per step: %d. Step num: %d",
		Timer,goPerStep,wassteps);
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
		drawColor=14;
  	break;
  	
  	case 5:
  		drawColor=0;
  	break;
  	
  	case 6:
  		drawColor=3;
  	break;
  	
  	case 7:
  		drawColor=4;
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
	glutAddMenuEntry("Bright white", 115);
	
	int submenu=glutCreateMenu(menu);
	glutAddMenuEntry("Sand", 4);
	glutAddMenuEntry("Eraser", 5);
	glutAddMenuEntry("Wall", 6);
	glutAddMenuEntry("Flame", 7);
	
 
	glutCreateMenu(menu);

	glutAddMenuEntry("Quit", 0);
	glutAddMenuEntry("Reset", 1);
	glutAddMenuEntry("Reload", 2);
	glutAddMenuEntry("Play/Pause", 3);
	glutAddSubMenu("Set tool",submenu);
  	glutAddSubMenu("Set color",collors);
  

	glutAttachMenu(GLUT_RIGHT_BUTTON);


}


////////////////////////////////////////////////////////



void to_end(void){
	if(steps>0){
		while(steps>0){
			goTurmit();
		}
	}else{
		cout<<"Невозможно";
	}

}

void many_go(void){
	cout<<endl<<"Сколько шагов выполнить:";
	int n;
	cin>>n;
	
	for(;n>0;n--)
		if(!goTurmit()){
			cerr<<"Невозможно";
			break;
		}
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
	x=y=10;
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
		
		case 115:			//r
			show_prog();
		break;
		
		
		
		case 13:
			if(!end)
				goTurmit();
		break;
	}
}

void special(int key,int x, int y){
//	clog<<key<<endl;
	
	switch (key){
		case 100:

		break;
		
		case 101:
			goPerStep+=100;
		break;
		
		case 102:

		break;
		
		case 103:
			goPerStep=(goPerStep-100>1?goPerStep-100:1);
		break;
	}
//	clog<<goPerStep<<endl;
}


void motion(int x,int y){
	int i,j;
	j=(x-SPSIZE)/(SQSIZE+SPSIZE);
	i=(y-SPSIZE)/(SQSIZE+SPSIZE);
	if(i+1<NPOLE&&j+1<NPOLE&&i>=0&&j>=0){
		area[i][j]=drawColor;
		area[i+1][j]=drawColor;
		area[i][j+1]=drawColor;
		area[i+1][j+1]=drawColor;
	}
}


int main(int Narg,char **arg){
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
	glutInitWindowSize(Npixels, Npixels);
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
