#include "Level.h"

Level::Level()
{
	GRID_SIZE = MIN_SIZE;
	GRID[GRID_SIZE][GRID_SIZE];
	
	initTiles();

	obstacles.clear();
}

Level::~Level()
{
}

void Level::initTiles()
{
	for (int i = 0; i < GRID_SIZE; ++i)
	{
		for (int j = 0; j < GRID_SIZE; ++j)
		{
			GRID[i][j].x_pos = i;
			GRID[i][j].y_pos = j;
		}
	}
}