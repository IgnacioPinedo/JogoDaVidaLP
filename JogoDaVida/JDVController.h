#include<GL/glut.h>
#include<stdio.h>

#define MatrixMax 100

int size, initiate, sleepTime, setInitGrid, setGenDet, runGenDet, qtdGenDet;

int Keys[256];

void execute();

void mouseController(int button, int state, int mousex, int mousey);

void arrowsController(int key, int x, int y);

void keyboardController(unsigned char key, int x, int y);

void idleFuncController();

void newGeneration();

void printInitGrid();