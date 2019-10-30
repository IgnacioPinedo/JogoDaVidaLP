#include "JDVModel.h"
#include "JDVView.h"
#include "JDVController.h"

void init()
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(50, 50);
}

void start(int size)
{
	//Escolhe a cor do fundo (preto)
	glClearColor(1.0, 0.0, 0.0, 0.0);
	//Cria a tela principal
	glutInitWindowSize(size, size);
	glutCreateWindow("Jogo da Vida LP");
	//desenha a grade na tela
	drawgrid(size);

	//gerencia entradas pelo mouse
	glutMouseFunc(mouse);

	//gerencia entradas pelas teclas de setas
	glutSpecialFunc(arrows);

	//gerencia teclas clicadas do teclado
	glutKeyboardFunc(keyboard);

	glutIdleFunc(idleFunc);

	glutMainLoop();
}

void killCell(float x, float y)
{
	glColor3f(0.0f, 0.0f, 0.0f);

	glPointSize(8);

	glBegin(GL_POINTS);
	glVertex2d(x, y);

	glEnd();

	glFlush();
}

void createCell(float x, float y)
{
	glColor3f(1.0f, 1.0f, 0.1f);

	glPointSize(8);

	glBegin(GL_POINTS);
	glVertex2d(x, y);

	glEnd();

	glFlush();
}

void toggleCell(float cellX, float cellY, int x, int y)
{
	if (existsOld(x, y) == 0)
	{
		createCell(cellX, cellY);
	}
	else if (existsOld(x, y) == 1)
	{
		killCell(cellX, cellY);
	}
}

void drawgrid(int size)
{
	int x;
	glColor3f(0.5, 0.5, 0.5);
	for (x = -size; x < size; x += 20)
	{
		float val = (float)x / size;
		glBegin(GL_LINES);
		glVertex3f(val, -1, 0);
		glVertex3f(val, 1, 0);
		glEnd();
		glFlush();
	}
	for (x = -size; x < size; x += 20)
	{
		float val = (float)x / size;
		glBegin(GL_LINES);
		glVertex3f(-1, val, 0);
		glVertex3f(1, val, 0);
		glEnd();
		glFlush();
	}

}

void mouse(int button, int state, int mousex, int mousey)
{
	mouseController(button, state, mousex, mousey);

	glutPostRedisplay();
}

void arrows(int key, int x, int y)
{
	arrowsController(key, x, y);
}

void keyboard(unsigned char key, int x, int y)
{
	keyboardController(key, x, y);
}

void idleFunc()
{
	idleFuncController();
}