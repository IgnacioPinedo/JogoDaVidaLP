#include "JDVModel.h"
#include "JDVView.h"
#include "JDVController.h"

void execute()
{
	char c = "";

	init();

	//Escolhe o tamanho da grade
	printf("Escolha o tamanho da grade (minimo 50 - maximo 100):\n");
	scanf("%d", &size);

	//limita o valor escolhido pelo usuario
	if (size < 50) size = 50;
	if (size > 100) size = 100;

	//seta o gerenciamento automatico para parado
	initiate = 0;

	//seta o valor do tempo de geracoes
	sleepTime = 1000;

	//Deixa o usuario carregar um arquivo
	printf("Voce deseja inserir os dados pelo arquivo data? ('s' para sim e 'n' para nao)\n");
	scanf(" %c", &c);

	if (c == 's')
	{
		readFile();
		setInitGrid = 1;
	}

	c = "";

	//Deixa o usuario determinar a quantidade de geracoes
	printf("Voce deseja selecionar o numero de geracoes? ('s' para sim e 'n' para nao)\n");
	scanf(" %c", &c);

	if (c == 's')
	{
		setGenDet = 1;

		//seta a quantidade de geracoes
		printf("Quantas geracoes voce deseja gerar? ('s' para sim e 'n' para nao)\n");
		scanf(" %d", &qtdGenDet);
	}

	size = size * 10;

	start(size);
}

void mouseController(int button, int state, int mousex, int mousey)
{
	int x, y;

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
			toggleCell(pointX, pointY, x, y);
			toggleGrid(x, y);
			toggleCell(pointX - add, pointY, x - 1, y);
			toggleGrid(x - 1, y);
			toggleCell(pointX, pointY + add, x, y + 1);
			toggleGrid(x, y + 1);
			toggleCell(pointX - add, pointY + add, x - 1, y + 1);
			toggleGrid(x - 1, y + 1);

			printf("Block!\n");
		}
		else if (Keys['2'] == 1)
		{
			toggleCell(pointX, pointY, x, y);
			toggleGrid(x, y);
			toggleCell(pointX - add, pointY + add, x - 1, y + 1);
			toggleGrid(x - 1, y + 1);
			toggleCell(pointX - add, pointY - add, x - 1, y - 1);
			toggleGrid(x - 1, y - 1);
			toggleCell(pointX - 2 * add, pointY + add, x - 2, y - 1);
			toggleGrid(x - 2, y - 1);
			toggleCell(pointX - 2 * add, pointY - add, x - 2, y + 1);
			toggleGrid(x - 2, y + 1);
			toggleCell(pointX - 3 * add, pointY, x - 3, y);
			toggleGrid(x - 3, y);

			printf("Hive!\n");
		}
		else if (Keys['3'] == 1)
		{
			toggleCell(pointX, pointY, x, y);
			toggleGrid(x, y);
			toggleCell(pointX, pointY + add, x, y - 1);
			toggleGrid(x, y - 1);
			toggleCell(pointX, pointY + 2 * add, x, y - 2);
			toggleGrid(x, y - 2);

			printf("Blinker!\n");
		}
		else if (Keys['4'] == 1)
		{
			toggleCell(pointX, pointY, x, y);
			toggleGrid(x, y);
			toggleCell(pointX - add, pointY, x - 1, y);
			toggleGrid(x - 1, y);
			toggleCell(pointX - 2 * add, pointY, x - 2, y);
			toggleGrid(x - 2, y);
			toggleCell(pointX - add, pointY - add, x - 1, y + 1);
			toggleGrid(x - 1, y + 1);
			toggleCell(pointX - 2 * add, pointY - add, x - 2, y + 1);
			toggleGrid(x - 2, y + 1);
			toggleCell(pointX - 3 * add, pointY - add, x - 3, y + 1);
			toggleGrid(x - 3, y + 1);

			printf("Toad!\n");
		}
		else if (Keys['5'] == 1)
		{
			toggleCell(pointX, pointY, x, y);
			toggleGrid(x, y);
			toggleCell(pointX - add, pointY, x - 1, y);
			toggleGrid(x - 1, y);
			toggleCell(pointX, pointY + add, x, y - 1);
			toggleGrid(x, y - 1);
			toggleCell(pointX - 2 * add, pointY + 3 * add, x - 2, y - 3);
			toggleGrid(x - 2, y - 3);
			toggleCell(pointX - 3 * add, pointY + 2 * add, x - 3, y - 2);
			toggleGrid(x - 3, y - 2);
			toggleCell(pointX - 3 * add, pointY + 3 * add, x - 3, y - 3);
			toggleGrid(x - 3, y - 3);

			printf("Beacon!\n");
		}
		else if (Keys['6'] == 1)
		{
			toggleCell(pointX, pointY, x, y);
			toggleGrid(x, y);
			toggleCell(pointX - add, pointY, x - 1, y);
			toggleGrid(x - 1, y);
			toggleCell(pointX, pointY + add, x, y - 1);
			toggleGrid(x, y - 1);
			toggleCell(pointX - 2 * add, pointY, x - 2, y);
			toggleGrid(x - 2, y);
			toggleCell(pointX - add, pointY + 2 * add, x - 1, y - 2);
			toggleGrid(x - 1, y - 2);

			printf("Glider!\n");
		}
		else if (Keys['7'] == 1)
		{
			toggleCell(pointX, pointY, x, y);
			toggleGrid(x, y);
			toggleCell(pointX - add, pointY, x - 1, y);
			toggleGrid(x - 1, y);
			toggleCell(pointX - 2 * add, pointY, x - 2, y);
			toggleGrid(x - 2, y);
			toggleCell(pointX - 3 * add, pointY, x - 3, y);
			toggleGrid(x - 3, y);
			toggleCell(pointX - 4 * add, pointY + add, x - 4, y - 1);
			toggleGrid(x - 4, y - 1);
			toggleCell(pointX, pointY + add, x, y - 1);
			toggleGrid(x, y - 1);
			toggleCell(pointX, pointY + 2 * add, x, y - 2);
			toggleGrid(x, y - 2);
			toggleCell(pointX - add, pointY + 3 * add, x - 1, y - 3);
			toggleGrid(x - 1, y - 3);
			toggleCell(pointX - 4 * add, pointY + 3 * add, x - 4, y - 3);
			toggleGrid(x - 4, y - 3);

			printf("LWSS!\n");
		}
		else if (Keys['8'] == 1)
		{
		toggleCell(pointX, pointY, x, y);
			toggleGrid(x, y);
			toggleCell(pointX - add, pointY, x - 1, y);
			toggleGrid(x - 1, y);
			toggleCell(pointX - 2 * add, pointY, x - 2, y);
			toggleGrid(x - 2, y);
			toggleCell(pointX - 3 * add, pointY, x - 3, y);
			toggleGrid(x - 3, y);
			toggleCell(pointX - 4 * add, pointY, x - 4, y);
			toggleGrid(x - 4, y);
			toggleCell(pointX - 5 * add, pointY + add, x - 5, y - 1);
			toggleGrid(x - 5, y - 1);
			toggleCell(pointX, pointY + add, x, y - 1);
			toggleGrid(x, y - 1);
			toggleCell(pointX, pointY + 2 * add, x, y - 2);
			toggleGrid(x, y - 2);
			toggleCell(pointX - add, pointY + 3 * add, x - 1, y - 3);
			toggleGrid(x - 1, y - 3);
			toggleCell(pointX - 5 * add, pointY + 3 * add, x - 5, y - 3);
			toggleGrid(x - 5, y - 3);
			toggleCell(pointX - 3 * add, pointY + 4 * add, x - 3, y - 4);
			toggleGrid(x - 3, y - 4);

			printf("MWSS!\n");
		}
		else if (Keys['9'] == 1)
		{
			toggleCell(pointX, pointY, x, y);
			toggleGrid(x, y);
			toggleCell(pointX - add, pointY, x - 1, y);
			toggleGrid(x - 1, y);
			toggleCell(pointX - 2 * add, pointY, x - 2, y);
			toggleGrid(x - 2, y);
			toggleCell(pointX - 3 * add, pointY, x - 3, y);
			toggleGrid(x - 3, y);
			toggleCell(pointX - 4 * add, pointY, x - 4, y);
			toggleGrid(x - 4, y);
			toggleCell(pointX - 5 * add, pointY, x - 5, y);
			toggleGrid(x - 5, y);
			toggleCell(pointX - 6 * add, pointY + add, x - 6, y - 1);
			toggleGrid(x - 6, y - 1);
			toggleCell(pointX, pointY + add, x, y - 1);
			toggleGrid(x, y - 1);
			toggleCell(pointX, pointY + 2 * add, x, y - 2);
			toggleGrid(x, y - 2);
			toggleCell(pointX - add, pointY + 3 * add, x - 1, y - 3);
			toggleGrid(x - 1, y - 3);
			toggleCell(pointX - 6 * add, pointY + 3 * add, x - 6, y - 3);
			toggleGrid(x - 6, y - 3);
			toggleCell(pointX - 3 * add, pointY + 4 * add, x - 3, y - 4);
			toggleGrid(x - 3, y - 4);
			toggleCell(pointX - 4 * add, pointY + 4 * add, x - 4, y - 4);
			toggleGrid(x - 4, y - 4);

			printf("HWSS!\n");
		}
		else
		{

			toggleCell(pointX, pointY, x, y);
			toggleGrid(x, y);

			x = 0;
			y = 0;
		}

		for (z = 0; z < 256; z++)
		{
			if (Keys[z] == 1) Keys[z] = 0;
		}
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)//right click
	{
		for (x = 0; x < size / 10; x++)
		{
			for (y = 0; y < size / 10; y++)
			{
				if (existsOld(x, y) != 0)
				{
					toggleGrid(x, y);

					float pointX = (float)(x * 20 - size + 10) / size;
					float pointY = -(float)(y * 20 - size + 10) / size;

					killCell(pointX, pointY);
				}
			}
		}
		x = 0;
		y = 0;
	}
}

void arrowsController(int key, int x, int y)
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

void keyboardController(unsigned char key, int x, int y)
{
	if (key == 13)
	{
		if (initiate == 0) initiate = 1;
		else if (initiate == 1) initiate = 0;
		printf("Enter pressed %d\n", initiate);
	}
	else if (setGenDet == 1 && key == 114)
	{
		runGenDet = 1;
		setGenDet = 0;
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

void idleFuncController()
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
	else if (runGenDet == 1)
	{
		int n;
		for (n = 0; n < qtdGenDet; n++)
		{
			newGeneration();
			glFlush();
			Sleep(sleepTime);
		}
		runGenDet = 0;
	}
}

void newGeneration()
{
	int x, y;

	for (x = 0; x < size / 10; x++)
	{
		for (y = 0; y < size / 10; y++)
		{
			if ((existsOld(x, y) == 0 && sumCellAdj(x, y) == 3) || (existsOld(x, y) == 1 && sumCellAdj(x, y) == 2) || (existsOld(x, y) == 1 && sumCellAdj(x, y) == 3))
			{
				setNew(x, y, 1);
			}
			else if ((existsOld(x, y) == 1 && sumCellAdj(x, y) >= 4) || (existsOld(x, y) == 1 && sumCellAdj(x, y) <= 4))
			{
				setNew(x, y, 0);
			}
			else
			{
				setNew(x, y, 0);
			}
		}
	}

	for (x = 0; x < size / 10; x++)
	{
		for (y = 0; y < size / 10; y++)
		{
			float pointX = (float)(x * 20 - size + 10) / size;
			float pointY = -(float)(y * 20 - size + 10) / size;

			if (existsNew(x, y) == 1 && existsOld(x, y) == 0)
			{
				assing(x, y);
				createCell(pointX, pointY);
			}
			else if (existsNew(x, y) == 0 && existsOld(x, y) == 1)
			{
				assing(x, y);
				killCell(pointX, pointY);
			}

			setNew(x, y, 0);
		}
	}

	x = 0;
	y = 0;
}

void printInitGrid()
{
	int x, y;

	for (x = 0; x < size / 10; x++)
	{
		for (y = 0; y < size / 10; y++)
		{
			if (existsOld(x, y) == 1)
			{
				float pointX = (float)(x * 20 - size + 10) / size;
				float pointY = -(float)(y * 20 - size + 10) / size;

				createCell(pointX, pointY);
			}
		}
	}
}