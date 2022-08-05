#include "Level.h"

Level::Level()
{
	GRID_SIZE = MIN_SIZE + 1;
	empty.loadFromFile("Utilities/spr_grass.png");

	initTiles();
}

Level::~Level()
{

}

void Level::Update(Input& input, sf::Clock* timer)
{
	if (input.pressedKey() == eINC_SIZE)
	{
		incSize(timer);
		timer->restart();
	}
	else if (input.pressedKey() == eDEC_SIZE)
	{
		decSize(timer);
		timer->restart();
	}
	else if (input.pressedKey() == eRESET)
	{
		reset();
		timer->restart();
	}
}

void Level::initTiles()
{
	for (int i = 0; i < MAX_SIZE; ++i)
	{
		for (int j = 0; j < MAX_SIZE; ++j)
		{
			auto cell = &GRID[i][j];
			cell->columnIndex = i;
			cell->rowIndex = j;
			cell->type = eEMPTY;
			cell->status = eINACTIVE;
			cell->tile_sprite.setPosition(sf::Vector2f(i * 50 + 130, j * 50 + 50));
			cell->tile_sprite.setTexture(empty);
		}
	}

}

void Level::reset()
{
	for (auto cell : GRID)
	{
		cell->type = eEMPTY;
	}

	for (int i = 0; i < GRID_SIZE; i++)
	{
		for (int j = 0; j < GRID_SIZE; j++)
		{
			switch (GRID[i][j].type)
			{
			case eEMPTY:
				GRID[i][j].tile_sprite.setTexture(empty);
				break;

			default:
				GRID[i][j].tile_sprite.setTexture(empty);
				break;
			}
			GRID[i][j].tile_sprite.setPosition(sf::Vector2f((100.f * i) + 50, (100.f * j) + 50));
		}
	}
}

void Level::incSize(sf::Clock* timer)
{
	if (timer->getElapsedTime().asMilliseconds() >= 50)
	{
		GRID_SIZE++;

		if (GRID_SIZE > MAX_SIZE)
			GRID_SIZE = MAX_SIZE;

		obstacles.clear();
		//generateExits();
		//generateObstacles();
	}
}

void Level::decSize(sf::Clock* timer)
{
	if (timer->getElapsedTime().asMilliseconds() >= 50)
	{
		GRID_SIZE--;

		if (GRID_SIZE < MIN_SIZE)
			GRID_SIZE = MIN_SIZE;

		obstacles.clear();
		//generateExits();
		//generateObstacles();
	}
}


void Level::generateExits()
{

}

void Level::generateObstacles()
{
	for (int i = 0; i < 2 * GRID_SIZE - 5; ++i)
	{
		int col = rand() % GRID_SIZE;
		int row = rand() % GRID_SIZE;

		for (int x = 0; x < GRID_SIZE; ++x)
		{
			for (int y = 0; y < GRID_SIZE; ++y)
			{
				if (GRID[col][row].type == eEMPTY && GRID[col - 1][row].type == eEMPTY &&
					GRID[col + 1][row].type == eEMPTY && GRID[col][row + 1].type == eEMPTY &&
					GRID[col + 1][row + 1].type == eEMPTY && GRID[col + 1][row - 1].type == eEMPTY &&
					GRID[col - 1][row + 1].type == eEMPTY && GRID[col - 1][row - 1].type == eEMPTY &&
					GRID[col][row - 1].type == eEMPTY && (col != 0 && col != GRID_SIZE - 1 && row != 0 && row != GRID_SIZE - 1))
				{
					GRID[col][row].type = eOBSTACLE;
					obstacles.emplace_back(&GRID[col][row]);
				}
			}
		}
	}
}

void Level::drawLevel(sf::RenderWindow* window)
{
	for (int i = 0; i < GRID_SIZE; ++i)
	{
		for (int j = 0; j < GRID_SIZE; ++j)
		{
			auto tile = &GRID[i][j];

			window->draw(tile->tile_sprite);
		}
	}
}