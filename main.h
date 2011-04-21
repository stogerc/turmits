#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <stdio.h>

#include <stdlib.h>
#include <time.h>

#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

#include <string.h>

#include <GL/glut.h>
#include <GL/freeglut_ext.h>


#define NPOLE 100
#define SQSIZE 5
#define SPSIZE 1
#define DBG 1




void turmit(void);

void draw(void);
void clear(void);
bool load(std::string);
void keymv(char);

void show_prog(void);
void show_info(void);

void left(void);
void right(void);
void go(void);
bool goTurmit(void);
void many_go(void);
void to_end(void);

void DrawOneStep(void);

#endif
