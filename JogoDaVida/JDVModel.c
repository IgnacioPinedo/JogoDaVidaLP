#include "JDVModel.h"
#include "JDVView.h"
#include "JDVController.h"

void toggleGrid(int x, int y)
{
	if (oldGrid[x][y] == 0)
	{
		oldGrid[x][y] = 1;
	}
	else if (oldGrid[x][y] == 1)
	{
		oldGrid[x][y] = 0;
	}
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

int existsOld(int x, int y)
{
	return oldGrid[x][y];
}

int existsNew(int x, int y)
{
	return newGrid[x][y];
}

void assing(int x, int y)
{
	oldGrid[x][y] = newGrid[x][y];
}

void setNew(int x, int y, int val)
{
	newGrid[x][y] = val;
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
}