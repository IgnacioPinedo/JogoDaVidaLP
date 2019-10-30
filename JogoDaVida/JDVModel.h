#include<stdio.h>

#define MatrixMax 100

int newGrid[MatrixMax][MatrixMax], oldGrid[MatrixMax][MatrixMax];

void toggleGrid(int x, int y);

int existsOld(int x, int y);

int existsNew(int x, int y);

void assing(int x, int y);

void setNew(int x, int y, int val);

int sumCellAdj(int xCurr, int yCurr);

void saveFile();

void readFile();