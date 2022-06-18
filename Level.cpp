#include "Level.h"

Level::Level(sf::RenderWindow& window)
{
	GRID_SIZE = MIN_SIZE;
	
	initTiles();

	obstacles.clear();

	empty.loadFromFile("UTILS/spr_grass.png");
	obstacle.loadFromFile("UTILS/spr_bush.png");
	exit.loadFromFile("UTILS/spr_exit.png");
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
			auto cell = &GRID[i][j];
			cell->columnIndex = i;
			cell->rowIndex = j;
			cell->type = TILE_TYPE::EMPTY;
			cell->tile_sprite.setTexture(empty);
		}
	}
}

void Level::drawLevel(sf::RenderWindow& window)
{
	for (int i = 0; i < GRID_SIZE; i++)
	{
		for (int j = 0; j < GRID_SIZE; j++)
		{
			window.draw(GRID[i][j].tile_sprite);
		}
	}
}