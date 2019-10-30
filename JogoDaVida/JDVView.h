#include<GL/glut.h>
#include<stdio.h>
#include <Windows.h>

void init();

void start(int size);

void mouse(int button, int state, int mousex, int mousey);

void killCell(float x, float y);

void createCell(float x, float y);

void toggleCell(float cellX, float cellY, int x, int y);

void drawgrid(int size);

void arrows(int key, int x, int y);

void keyboard(unsigned char key, int x, int y);

void idleFunc();