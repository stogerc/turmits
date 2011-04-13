#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <cstdlib>
#include <unistd.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <vector>
#include <GL/glut.h>
#include <string>
#include <fstream>
#include <sys/wait.h>

#define NPOLE 100
#define SQSIZE 5
#define SPSIZE 1
#define TIMER 0

int Npixels=NPOLE*SQSIZE+(NPOLE+1)*SPSIZE;
int PID;

struct TerminalOpt {
        TerminalOpt() {
                termios new_settings;
                tcgetattr(0,&stored_settings);
                new_settings = stored_settings;
                new_settings.c_lflag &= (~ICANON);
                new_settings.c_cc[VTIME] = 0;
                new_settings.c_cc[VMIN] = 1;
                tcsetattr(0,TCSANOW,&new_settings);
        }
        ~TerminalOpt() {
                tcsetattr(0,TCSANOW,&stored_settings);
        }
        termios stored_settings;
};

using namespace std;

///////////////////////////////////////////////////////////


	void turmit(void);
	
	void draw(void);
	void clear(void);
	void load(char[]);
	void keymv(char);
	
	void show_prog(void);
	void show_info(void);
	
	void left(void);
	void right(void);
	void go(void);
	bool goTurmit(void);
	void many_go(void);
	void to_end(void);
	
///////////////////////////////////////////////////////////

	int  **area;
	
	struct turmline{
		string	state;
		int		color;
		int		Ncolor;
		int		rotate;
		string	Nstate;
	};
	
	
	vector<turmline> prog;
	
	int steps;
	int Asteps;
	string qState;
	int qLine;
	char filename[100];
	
	int x,y;
	int look;
	bool end=false;
	bool ispause=true;

////////////////////////////////////////////////////


void Reshape(int width, int height){
	glLoadIdentity();
	gluOrtho2D(0, Npixels,0, Npixels);
}

void Draw(void){

	if((!end)&&ispause)
		if(!goTurmit()){
			end=true;					
		}


	double r,g,b;
	glClear(GL_COLOR_BUFFER_BIT);

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
			
			
			
			glRectf((i*(SQSIZE+SPSIZE)+1),
			(j*(SQSIZE+SPSIZE)+1),
			(i*(SQSIZE+SPSIZE)+SQSIZE+1),
			(j*(SQSIZE+SPSIZE)+SQSIZE+1));

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


void timf(int value){
	glutPostRedisplay();
	glutTimerFunc(TIMER, timf, 0);
}

void menu(int value){
  switch(value){
  
  	case 0:
 	 	kill(PID,SIGTERM);
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
 
  int menid = glutCreateMenu(menu);

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
	if(steps!=-1){
		if(steps>0)
			steps--;
		else{
			cout<<"Шаги закончились";
			return 0;
		}
	}
	unsigned int i;
	for(i=0;i<prog.size();i++){
		
		if(((prog[i].state==qState)||prog[i].state=="*")
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
			}
			if(prog[i].Nstate!="*"){
				qState.clear();
				qState=prog[i].Nstate;
			}
			qLine=i;
			break;
		}
	}
	
	
			
	return 1;
	
}


void load(char *fname){
	
	prog.clear();
	steps=-1;
	Asteps=-1;
	
	string newstr;
	char ctemp;
	string stemp;
	
	if(fname==NULL){
		cout<<"Имяфайла:";
		cin>>filename;	
	}
	else
		strcpy(filename,fname);

	ifstream ifs(filename);
	
	ifs>>newstr;
	
	while(!ifs.eof()){
		if(newstr.find_first_of(";")==0){
			ctemp='a';
				while(ctemp!='\n'){
					ctemp=ifs.get();
				}
		}else{
			if(newstr.find_first_of("#")==0){

				if(newstr.length()>1){
					stemp.clear();
					stemp=newstr.substr(newstr.find_first_of("#")+1);
					steps=atoi(stemp.c_str());
					stemp.clear();
				}else
					ifs>>steps;
				Asteps=steps;
				ctemp='a';
				while(ctemp!='\n')
					ctemp=ifs.get();
			}else{
				turmline nl;
				nl.state=newstr;
				ifs>>nl.color;
				ifs>>nl.Ncolor;
				ifs>>nl.rotate;
				ifs>>nl.Nstate;
				stemp.clear();
				stemp=nl.Nstate.substr(0,nl.Nstate.find_first_of(";"));
				nl.Nstate.clear();
				nl.Nstate=stemp;
				stemp.clear();
//				clog<<nl.state<<" "
//				<<nl.color<<" "
//				<<nl.Ncolor<<" "
//				<<nl.rotate<<" "
//				<<nl.Nstate<<endl;
				
				
				prog.push_back(nl);
				ctemp='a';
				while(ctemp!='\n')
					ctemp=ifs.get();
				
			}
		}	
		ifs>>newstr;
	}
	qState=prog[0].state;
	clear();

}



//void load(char *fname){
//	prog.clear();

//	char symb,temp;
//	if(fname==NULL){
//		cout<<"Имяфайла:";
//		cin>>filename;	
//	}
//	else
//		strcpy(filename,fname);
//	FILE *progfile;
//	steps=-1;
//	
//	if(!(progfile=fopen(filename,"r")))
//		cout<<"Нет файла =(";
//	else{
//		symb=getc(progfile);
//		while(!feof(progfile)){

//			switch(symb){
//				
//				case 10:

//				break;
//				
//				case 32:
//					temp='a';
//					while(temp!='\n')
//						temp=getc(progfile);
//				break;
//			
//			
//				case ';':
//					temp='a';
//					while(temp!='\n')
//						temp=getc(progfile);
//				break;
//				
//				case '#':
//					fscanf(progfile,"%d",&steps);
//					temp='a';
//					while(temp!='\n')
//						temp=getc(progfile);
//					
//				break;

//				default:
//					turmline nl;
//					nl.state=symb;

//					fscanf(progfile,"%d %d %d ",
//						&nl.color,&nl.Ncolor,&nl.rotate);
//						
//					fscanf(progfile,"%c",&nl.Nstate);

//					prog.push_back(nl);
//					
//					temp='a';
//					while(temp!='\n')
//						temp=getc(progfile);
//			
//				break;			
//			}
//			symb=getc(progfile);
//		
//		}
//		
//		qState=prog[0].state;

//	}
//	clear();
//	fclose(progfile);
//	x=y=20;
//	look=1;
//	lookc='>';
//}



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


void turmit(void){
	int i,j;
	area=new int *[NPOLE];


	for(i=0;i<NPOLE;i++){
		area[i]=new int [NPOLE];

		for(j=0;j<NPOLE;j++)
			area[i][j]=0;
	}
	
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






void keymv(char a){
		
	switch(a){
		
		case 10:
			goTurmit();
		break;
	
		case 99:
			clear();
		break;
		
		case 113:
			cout<<"-выход."<<endl;
		break;
				
		case 108:
			load(NULL);
		break;
		
		case 114:
			load(filename);
		break;
		
		case 109:
			many_go();
		break;
		
		case 100:
			to_end();
		break;
				
		default:
			cout<<"?"<<endl;
		break;
	
	}



}


int main(int Narg,char **arg){
	TerminalOpt term;
	turmit();
	char a;
	unsigned int step=0;
	if(Narg>1){
		load(arg[1]);
		Narg--;
		arg++;
	}
	else
		load(NULL);
//	mytu.show_prog();
	
	bool end=false;
 
	glutInit(&Narg, arg);
	glutInitWindowSize(Npixels, Npixels);
	(void)glutCreateWindow("turmits");
	createMenu();

	glutReshapeFunc(Reshape);
	glutDisplayFunc(Draw);
	glutTimerFunc(0, timf, 0);

	glutMainLoop();
	
	
	return 0;
}
