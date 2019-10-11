#include<GL/glut.h>
#include<stdio.h>
#include <Windows.h>

#define MatrixMax 100

int newGrid[MatrixMax][MatrixMax], oldGrid[MatrixMax][MatrixMax], x, y, size, initiate, sleepTime;

void myinit();

void drawgrid(int size);

void mouse(int button, int state, int mousex, int mousey);

void arrows(int key, int x, int y);

void keyboard(unsigned char key, int x, int y);

void autoGenerate();

void newGeneration();

void killCell(float x, float y);

void createCell(float x, float y);

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(50, 50);

	//Escolhe o tamanho da grade
	printf("escolha o tamanho da grade (minimo 50 - maximo 100):\n");
	scanf_s("%d", &size);

	//limita o valor escolhido pelo usuario
	if (size < 50) size = 50;
	if (size > 100) size = 100;

	//seta o gerenciamento automatico para parado
	initiate = 0;

	//seta o valor do tempo de geracoes
	sleepTime = 1000;

	//Seta o tamanho da grade
	size = size * 10;
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

	//gerencia entradas pelo teclado
	glutKeyboardFunc(keyboard);

	//glutDisplayFunc(autoGenerate);

	glutIdleFunc(autoGenerate);

	glutMainLoop();
}

void myinit()
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
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
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)//left click
	{
		x = mousex / 10;
		y = mousey / 10;

		float pointX = (float)(x * 20 - size + 10) / size;
		float pointY = -(float)(y * 20 - size + 10) / size;

		if (oldGrid[x][y] == 0)
		{
			oldGrid[x][y] = 1;
			createCell(pointX, pointY);
		}
		else if (oldGrid[x][y] == 1)
		{
			oldGrid[x][y] = 0;
			killCell(pointX, pointY);
		}

		x = 0;
		y = 0;
	}

	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)//right click
	{
		for (x = 0; x < size / 10; x++)
		{
			for (y = 0; y < size / 10; y++)
			{
				if (oldGrid[x][y] != 0)
				{
					oldGrid[x][y] = 0;

					float pointX = (float)(x * 20 - size + 10) / size;
					float pointY = -(float)(y * 20 - size + 10) / size;

					killCell(pointX, pointY);
				}
			}
		}
		x = 0;
		y = 0;
	}
	glutPostRedisplay();
}

void arrows(int key, int x, int y)
{
	if (key == GLUT_KEY_LEFT)
	{
		//printf("Left key is pressed\n");
	}
	else if (key == GLUT_KEY_RIGHT)
	{

		newGeneration();

		//printf("Right key is pressed\n");
	}
	else if (key == GLUT_KEY_DOWN)
	{
		if (sleepTime >= 500)
		{
			sleepTime -= 250;
		}
	}
	else if (key == GLUT_KEY_UP)
	{
		sleepTime += 250;
	}
}

void keyboard(unsigned char key, int x, int y)
{
	if (key == 13)
	{
		if (initiate == 0) initiate = 1;
		else if (initiate == 1) initiate = 0;
		printf("Enter pressed %d\n", initiate);
	}
}

void autoGenerate()
{
	if (initiate == 1)
	{
		newGeneration();
		Sleep(sleepTime);
	}
}

void newGeneration()
{
	for (x = 0; x < size / 10; x++)
	{
		for (y = 0; y < size / 10; y++)
		{
			if ((oldGrid[x][y] == 0 && sumCellAdj(x, y) == 3) || (oldGrid[x][y] == 1 && sumCellAdj(x, y) == 2) || (oldGrid[x][y] == 1 && sumCellAdj(x, y) == 3))
			{
				newGrid[x][y] = 1;
			}
			else if ((oldGrid[x][y] == 1 && sumCellAdj(x, y) >= 4) || (oldGrid[x][y] == 1 && sumCellAdj(x, y) <= 4))
			{
				newGrid[x][y] = 0;
			}
			else
			{
				newGrid[x][y] = 0;
			}
		}
	}

	for (x = 0; x < size / 10; x++)
	{
		for (y = 0; y < size / 10; y++)
		{
			float pointX = (float)(x * 20 - size + 10) / size;
			float pointY = -(float)(y * 20 - size + 10) / size;

			if (newGrid[x][y] == 1 && oldGrid[x][y] == 0)
			{
				oldGrid[x][y] = newGrid[x][y];
				createCell(pointX, pointY);
			}
			else if (newGrid[x][y] == 0 && oldGrid[x][y] == 1)
			{
				oldGrid[x][y] = newGrid[x][y];
				killCell(pointX, pointY);
			}


			newGrid[x][y] = 0;
		}
	}

	x = 0;
	y = 0;
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

int sumCellAdj(int xCurr, int yCurr)
{
	int xAux, yAux, sum, xSearch, ySearch;
	sum = 0;

	for (xAux = -1; xAux <= 1; xAux++)
	{
		for (yAux = -1; yAux <= 1; yAux++)
		{
			xSearch = xCurr + xAux;
			ySearch = yCurr + yAux;

			if (xSearch < 0) xSearch = 0;
			if (ySearch < 0) ySearch = 0;

			if (!(xAux == 0 && yAux == 0))
			{
				sum += oldGrid[xSearch][ySearch];
			}
		}
	}

	return sum;
}