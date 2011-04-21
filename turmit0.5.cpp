/*
	- Количество сделанных шагов
	+ Режим совместимости с грёбанной виндовой версией
	+ Доработать goTurmit не надо
	- Добавить makefile
	+ Много времени на отрисовку клеток
	- Смешать режим нескольких шагов и обычный
	- Вывод текста в обычном режиме
*/
#include "main.h"
using namespace std;

int Npixels=NPOLE*SQSIZE+(NPOLE+1)*SPSIZE;


	
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
	string qState;
	int qLine;
	string filename;
	
	int x,y,tx,ty;
	int look;
	bool end=false;
	bool ispause=true;
	int Timer=0;
	bool IfMany=false;
	int goPerStep=1000;

////////////////////////////////////////////////////


void Reshape(int width, int height){
	glLoadIdentity();
	gluOrtho2D(0, Npixels+2,0, Npixels+2+11);
}



void DrawManySteps(void){

	for(int i=0;i<goPerStep;i++){
		if((!end)&&ispause)
			if(!goTurmit())
				end=true;					
	}
	double r,g,b;
	glClear(GL_COLOR_BUFFER_BIT);	
			
			
	glColor3f(1,1,1);
	glRasterPos2f(SPSIZE+2,Npixels);
	char stroka[100];
	sprintf(stroka,"Pause between steps: %d ms.",Timer);
	glutBitmapString(GLUT_BITMAP_HELVETICA_10 ,(const unsigned char*) stroka );
      
	for(int i=0;i<NPOLE;i++)
		for(int j=0;j<NPOLE;j++){

			
			switch(area[NPOLE-j-1][i]){
				
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
			
			glColor3f(r,g,b);
			
			
			glRectf((i*(SQSIZE+SPSIZE)+SPSIZE),
			(j*(SQSIZE+SPSIZE)+SPSIZE),
			(i*(SQSIZE+SPSIZE)+SQSIZE+SPSIZE),
			(j*(SQSIZE+SPSIZE)+SQSIZE+SPSIZE));

			if(((NPOLE-j-1)==x)&&(i==y)){

				if(area[(NPOLE-j-1)][i]==15)
						glColor3f(0.0f,0.0f,0.0f);
					else
						glColor3f(1.0f,1.0f,1.0f);

				switch(look){
					case 1:
						glBegin(GL_TRIANGLES);
    					glVertex2f(( i*(SQSIZE+SPSIZE)+1),
    								(j*(SQSIZE+SPSIZE)+1));
    					glVertex2f(( i*(SQSIZE+SPSIZE)+1),
    								(j*(SQSIZE+SPSIZE)+1+SQSIZE));
    					glVertex2f(( i*(SQSIZE+SPSIZE)+1+SQSIZE),
    								(j*(SQSIZE+SPSIZE)+1+SQSIZE/2.));
    					glEnd();
					break;
					
					case 0:
							glBegin(GL_TRIANGLES);
    					glVertex2f(( i*(SQSIZE+SPSIZE)+1),
    								(j*(SQSIZE+SPSIZE)+1));
    					glVertex2f(( i*(SQSIZE+SPSIZE)+1+SQSIZE),
    								(j*(SQSIZE+SPSIZE)+1));
    					glVertex2f(( i*(SQSIZE+SPSIZE)+1+SQSIZE/2.),
    								(j*(SQSIZE+SPSIZE)+1+SQSIZE));
    					glEnd();
					break;
					
					case 3:
							glBegin(GL_TRIANGLES);
    					glVertex2f(( i*(SQSIZE+SPSIZE)+1+SQSIZE),
    								(j*(SQSIZE+SPSIZE)+1));
    					glVertex2f(( i*(SQSIZE+SPSIZE)+1+SQSIZE),
    								(j*(SQSIZE+SPSIZE)+1+SQSIZE));
    					glVertex2f(( i*(SQSIZE+SPSIZE)+1),
    								(j*(SQSIZE+SPSIZE)+1+SQSIZE/2.));
    					glEnd();

					break;
					
					case 2:
							glBegin(GL_TRIANGLES);
    					glVertex2f(( i*(SQSIZE+SPSIZE)+1+SQSIZE/2.),
    								(j*(SQSIZE+SPSIZE)+1));
    					glVertex2f(( i*(SQSIZE+SPSIZE)+1+SQSIZE),
    								(j*(SQSIZE+SPSIZE)+1+SQSIZE));
    					glVertex2f(( i*(SQSIZE+SPSIZE)+1),
    								(j*(SQSIZE+SPSIZE)+1+SQSIZE));
    					glEnd();

					break;
					
				}
			
			}


		}

	glutSwapBuffers();
}


void Draw(void){
	if(IfMany)
		DrawManySteps();
	else
		DrawOneStep();
}


void DrawOneStep(void){
	int i,j;
	if((!end)&&ispause)
		if(!goTurmit())
			end=true;			
	double r,g,b;
//	glClear(GL_COLOR_BUFFER_BIT);	
			
			
	//glColor3f(1,1,1);
	//glRasterPos2f(SPSIZE+2,Npixels);
	//char stroka[100];
	//sprintf(stroka,"Pause between steps: %d ms.",Timer);
	//glutBitmapString(GLUT_BITMAP_HELVETICA_10 ,
	//		(const unsigned char*) stroka );
      
	i=ty;
	j=(NPOLE-tx-1);
			
	switch(area[NPOLE-j-1][i]){
		
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
			
	glColor3f(r,g,b);
			
			
	glRectf((i*(SQSIZE+SPSIZE)+SPSIZE),
		(j*(SQSIZE+SPSIZE)+SPSIZE),
		(i*(SQSIZE+SPSIZE)+SQSIZE+SPSIZE),
		(j*(SQSIZE+SPSIZE)+SQSIZE+SPSIZE));

	i=y;
	j=(NPOLE-x-1);

	if(area[(NPOLE-j-1)][i]==15)
		glColor3f(0.0f,0.0f,0.0f);
	else
		glColor3f(1.0f,1.0f,1.0f);

	switch(look){
		case 1:
			glBegin(GL_TRIANGLES);
			glVertex2f(( i*(SQSIZE+SPSIZE)+1),
						(j*(SQSIZE+SPSIZE)+1));
			glVertex2f(( i*(SQSIZE+SPSIZE)+1),
						(j*(SQSIZE+SPSIZE)+1+SQSIZE));
			glVertex2f(( i*(SQSIZE+SPSIZE)+1+SQSIZE),
						(j*(SQSIZE+SPSIZE)+1+SQSIZE/2.));
			glEnd();
		break;
		
		case 0:
			glBegin(GL_TRIANGLES);
			glVertex2f(( i*(SQSIZE+SPSIZE)+1),
						(j*(SQSIZE+SPSIZE)+1));
			glVertex2f(( i*(SQSIZE+SPSIZE)+1+SQSIZE),
						(j*(SQSIZE+SPSIZE)+1));
			glVertex2f(( i*(SQSIZE+SPSIZE)+1+SQSIZE/2.),
						(j*(SQSIZE+SPSIZE)+1+SQSIZE));
			glEnd();
		break;
					
		case 3:
			glBegin(GL_TRIANGLES);
			glVertex2f(( i*(SQSIZE+SPSIZE)+1+SQSIZE),
						(j*(SQSIZE+SPSIZE)+1));
			glVertex2f(( i*(SQSIZE+SPSIZE)+1+SQSIZE),
						(j*(SQSIZE+SPSIZE)+1+SQSIZE));
			glVertex2f(( i*(SQSIZE+SPSIZE)+1),
						(j*(SQSIZE+SPSIZE)+1+SQSIZE/2.));
			glEnd();

		break;
					
		case 2:
			glBegin(GL_TRIANGLES);
			glVertex2f(( i*(SQSIZE+SPSIZE)+1+SQSIZE/2.),
						(j*(SQSIZE+SPSIZE)+1));
			glVertex2f(( i*(SQSIZE+SPSIZE)+1+SQSIZE),
						(j*(SQSIZE+SPSIZE)+1+SQSIZE));
			glVertex2f(( i*(SQSIZE+SPSIZE)+1),
						(j*(SQSIZE+SPSIZE)+1+SQSIZE));
			glEnd();

		break;
					
	}

	glutSwapBuffers();
}


void timf(int value){
	glutPostRedisplay();
	glutTimerFunc(Timer, timf, 0);
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
  
  }
  
  glutPostRedisplay();
}

void createMenu(void){
 
  glutCreateMenu(menu);

  glutAddMenuEntry("Quit", 0);
  glutAddMenuEntry("Reset", 1);
  glutAddMenuEntry("Reload", 2);
  glutAddMenuEntry("Play/Pause", 3);
  

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
		goTurmit();



}


void show_info(void){
	cout<<"Текущее состояние:"<<qState<<endl;
	cout<<"Цвет поля:"<<area[x][y]<<endl;
	cout<<"Термит ждёт цвет:"<<prog[qLine].color<<endl;
	
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

	if(steps>0)
		steps--;
	else
		if(steps==0){
			cout<<"Шаги закончились";
			if(DBG)
				exit(0);
			return 0;
		}

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
	ty=y;
	tx=x;

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


void turmit(void){
	area=new int *[NPOLE];

	for(int i=0;i<NPOLE;i++)
		area[i]=new int [NPOLE];
	
	x=y=NPOLE/2;
	look=1;
}


void clear(void){
	for(int i=0;i<NPOLE;i++)
		for(int j=0;j<NPOLE;j++)
			area[i][j]=0;
	qState=prog[0].state;
	x=y=NPOLE/2;
	look=1;
	steps=Asteps;
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
		
		case 27:			//q
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


int main(int Narg,char **arg){
	turmit();
	
	if(getopt(Narg,arg,"m::")=='m'){
		IfMany=true;
			if(optarg){
				goPerStep=atoi(optarg);
			}
		Narg--;
		arg++;
	}
	
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
	

	glutMainLoop();
	
	
	return 0;
}
