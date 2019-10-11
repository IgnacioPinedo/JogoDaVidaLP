#include<GL/glut.h>
#include<stdio.h>
#include <Windows.h>

#define MatrixMax 100

int newGrid[MatrixMax][MatrixMax], oldGrid[MatrixMax][MatrixMax], x, y, size, initiate, sleepTime, setInitGrid;

int Keys[256];

void myinit();

void drawgrid(int size);

void mouse(int button, int state, int mousex, int mousey);

void arrows(int key, int x, int y);

void keyboard(unsigned char key, int x, int y);

void toggleGrid(int xAux, int yAux);

void idleFunc();

void newGeneration();

void readFile();

void printInitGrid();

void killCell(float x, float y);

void createCell(float x, float y);

int main(int argc, char** argv)
{
	char f = "";

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(50, 50);

	//Escolhe o tamanho da grade
	printf("escolha o tamanho da grade (minimo 50 - maximo 100):\n");
	scanf("%d", &size);

	//limita o valor escolhido pelo usuario
	if (size < 50) size = 50;
	if (size > 100) size = 100;
	
	//seta o gerenciamento automatico para parado
	initiate = 0;

	//seta o valor do tempo de geracoes
	sleepTime = 1000;

	//Escolhe o tamanho da grade
	printf("Voce deseja inserir os dados pelo arquivo data? ('s' para sim e 'n' para nao)\n");
	scanf(" %c", &f);

	if (f == 's')
	{
		readFile();
	}

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

	//gerencia teclas clicadas do teclado
	glutKeyboardFunc(keyboard);

	glutIdleFunc(idleFunc);

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
		int z;

		x = mousex / 10;
		y = mousey / 10;

		float pointX = (float)(x * 20 - size + 10) / size;
		float pointY = -(float)(y * 20 - size + 10) / size;
		float add = (float)20 / size;

		if (Keys['1'] == 1)
		{
			toggleGrid(x, y);
			createCell(pointX, pointY);
			toggleGrid(x - 1, y);
			createCell(pointX - add, pointY);
			toggleGrid(x, y + 1);
			createCell(pointX, pointY + add);
			toggleGrid(x - 1, y + 1);
			createCell(pointX - add, pointY + add);

			printf("Block!\n");
		}
		else if (Keys['2'] == 1)
		{
			toggleGrid(x, y);
			createCell(pointX, pointY);
			toggleGrid(x - 1, y + 1);
			createCell(pointX - add, pointY + add);
			toggleGrid(x - 1, y - 1);
			createCell(pointX - add, pointY - add);
			toggleGrid(x - 2, y - 1);
			createCell(pointX - 2 * add, pointY + add);
			toggleGrid(x - 2, y + 1);
			createCell(pointX - 2 * add, pointY - add);
			toggleGrid(x - 3, y);
			createCell(pointX - 3 * add, pointY);

			printf("Hive!\n");
		}
		else if (Keys['3'] == 1)
		{
			toggleGrid(x, y);
			createCell(pointX, pointY);
			toggleGrid(x, y - 1);
			createCell(pointX, pointY + add);
			toggleGrid(x, y - 2);
			createCell(pointX, pointY + 2 * add);

			printf("Blinker!\n");
		}
		else if (Keys['4'] == 1)
		{
			toggleGrid(x, y);
			createCell(pointX, pointY);
			toggleGrid(x - 1, y);
			createCell(pointX - add, pointY);
			toggleGrid(x - 2, y);
			createCell(pointX - 2 * add, pointY);
			toggleGrid(x, y + 1);
			createCell(pointX, pointY - add);
			toggleGrid(x - 1, y + 1);
			createCell(pointX - add, pointY - add);
			toggleGrid(x - 2, y + 1);
			createCell(pointX - 2 * add, pointY - add);

			printf("Toad!\n");
		}
		else if (Keys['5'] == 1)
		{
			toggleGrid(x, y);
			createCell(pointX, pointY);
			toggleGrid(x - 1, y);
			createCell(pointX - add, pointY);
			toggleGrid(x, y - 1);
			createCell(pointX, pointY + add);
			toggleGrid(x - 2, y - 3);
			createCell(pointX - 2 * add, pointY + 3 * add);
			toggleGrid(x - 3, y - 2);
			createCell(pointX - 3 * add, pointY + 2 * add);
			toggleGrid(x - 3, y - 3);
			createCell(pointX - 3 * add, pointY + 3 * add);

			printf("Beacon!\n");
		}
		else if (Keys['6'] == 1)
		{
			toggleGrid(x, y);
			createCell(pointX, pointY);
			toggleGrid(x - 1, y);
			createCell(pointX - add, pointY);
			toggleGrid(x, y - 1);
			createCell(pointX, pointY + add);
			toggleGrid(x - 2, y);
			createCell(pointX - 2 * add, pointY);
			toggleGrid(x - 1, y - 2);
			createCell(pointX - add, pointY + 2 * add);

			printf("Glider!\n");
		}
		else if (Keys['7'] == 1)
		{
			toggleGrid(x, y);
			createCell(pointX, pointY);
			toggleGrid(x - 1, y);
			createCell(pointX - add, pointY);
			toggleGrid(x - 2, y);
			createCell(pointX - 2 * add, pointY);
			toggleGrid(x - 3, y);
			createCell(pointX - 3 * add, pointY);
			toggleGrid(x - 4, y - 1);
			createCell(pointX - 4 * add, pointY + add);
			toggleGrid(x, y - 1);
			createCell(pointX, pointY + add);
			toggleGrid(x, y - 2);
			createCell(pointX, pointY + 2 * add);
			toggleGrid(x - 1, y - 3);
			createCell(pointX - add, pointY + 3 * add);
			toggleGrid(x - 4, y - 3);
			createCell(pointX - 4 * add, pointY + 3 * add);

			printf("LWSS!\n");
		}
		else if (Keys['8'] == 1)
		{
			toggleGrid(x, y);
			createCell(pointX, pointY);
			toggleGrid(x - 1, y);
			createCell(pointX - add, pointY);
			toggleGrid(x - 2, y);
			createCell(pointX - 2 * add, pointY);
			toggleGrid(x - 3, y);
			createCell(pointX - 3 * add, pointY);
			toggleGrid(x - 4, y);
			createCell(pointX - 4 * add, pointY);
			toggleGrid(x - 5, y - 1);
			createCell(pointX - 5 * add, pointY + add);
			toggleGrid(x, y - 1);
			createCell(pointX, pointY + add);
			toggleGrid(x, y - 2);
			createCell(pointX, pointY + 2 * add);
			toggleGrid(x - 1, y - 3);
			createCell(pointX - add, pointY + 3 * add);
			toggleGrid(x - 5, y - 3);
			createCell(pointX - 5 * add, pointY + 3 * add);
			toggleGrid(x - 3, y - 4);
			createCell(pointX - 3 * add, pointY + 4 * add);

			printf("MWSS!\n");
		}
		else if (Keys['9'] == 1)
		{
			toggleGrid(x, y);
			createCell(pointX, pointY);
			toggleGrid(x - 1, y);
			createCell(pointX - add, pointY);
			toggleGrid(x - 2, y);
			createCell(pointX - 2 * add, pointY);
			toggleGrid(x - 3, y);
			createCell(pointX - 3 * add, pointY);
			toggleGrid(x - 4, y);
			createCell(pointX - 4 * add, pointY);
			toggleGrid(x - 5, y);
			createCell(pointX - 5 * add, pointY);
			toggleGrid(x - 6, y - 1);
			createCell(pointX - 6 * add, pointY + add);
			toggleGrid(x, y - 1);
			createCell(pointX, pointY + add);
			toggleGrid(x, y - 2);
			createCell(pointX, pointY + 2 * add);
			toggleGrid(x - 1, y - 3);
			createCell(pointX - add, pointY + 3 * add);
			toggleGrid(x - 6, y - 3);
			createCell(pointX - 6 * add, pointY + 3 * add);
			toggleGrid(x - 3, y - 4);
			createCell(pointX - 3 * add, pointY + 4 * add);
			toggleGrid(x - 4, y - 4);
			createCell(pointX - 4 * add, pointY + 4 * add);

			printf("HWSS!\n");
		}
		else
		{

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

		for (z = 0; z < 256; z++)
		{
			if(Keys[z] == 1) Keys[z] = 0;
		}
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

void saveFile()
{
	int i;
	int j;

	FILE* file;
	file = fopen("data.txt", "w");

	for (i = 0; i < MatrixMax; i++)
	{
		for (j = 0; j < MatrixMax; j++)
		{
			fprintf(file, "%d ", oldGrid[i][j]);
		}
		fprintf(file, "\n");
	}
	fclose(file);
}


void readFile()
{
	int i;
	int j;

	FILE* file;
	file = fopen("data.txt", "r");

	for (i = 0; i < MatrixMax; i++)
	{
		for (j = 0; j < MatrixMax; j++)
		{
			fscanf(file, "%d", &oldGrid[i][j]);
		}
	}
	fclose(file);

	setInitGrid = 1;
}

void printInitGrid()
{
	for (x = 0; x < size / 10; x++)
	{
		for (y = 0; y < size / 10; y++)
		{
			if (oldGrid[x][y] == 1)
			{
				float pointX = (float)(x * 20 - size + 10) / size;
				float pointY = -(float)(y * 20 - size + 10) / size;

				createCell(pointX, pointY);
			}
		}
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
	else if (key == 115)
	{
		saveFile();
		exit(0);
	}
	else
	{
		Keys[key] = 1;
	}
}

void idleFunc()
{
	if (initiate == 1)
	{
		newGeneration();
		Sleep(sleepTime);
	}
	else if (setInitGrid == 1)
	{
		printInitGrid();
		setInitGrid = 0;
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

void toggleGrid(int xAux, int yAux) 
{
	if (oldGrid[xAux][yAux] == 0)
	{
		oldGrid[xAux][yAux] = 1;
	}
	else if (oldGrid[x][y] == 1)
	{
		oldGrid[xAux][yAux] = 0;
	}
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