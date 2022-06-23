#include "Level.h"

Level::Level()
{
	GRID_SIZE = MIN_SIZE;
	
	initTiles();

	empty.loadFromFile("UTILS/spr_grass.png");
	obstacle.loadFromFile("UTILS/spr_bush.png");
	exit.loadFromFile("UTILS/spr_exit.png");
}

Level::~Level()
{
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
			cell->type = TILE_TYPE::EMPTY;
			cell->tile_sprite.setScale(sf::Vector2f(2.0f, 2.0f));
		}
	}

	generateExits();
	generateObstacles();
}

void Level::generateExits()
{
	NORTH_x = rand() % GRID_SIZE;
	NORTH_y = 0;

	if (NORTH_x == GRID_SIZE - 1)
		NORTH_x--;
	else if (NORTH_x == 0)
		NORTH_x++;
	else
		NORTH_x = NORTH_x;

	SOUTH_x = rand() % GRID_SIZE;
	SOUTH_y = GRID_SIZE - 1;

	if (SOUTH_x == GRID_SIZE - 1)
		SOUTH_x--;
	else if (SOUTH_x == 0)
		SOUTH_x++;
	else
		SOUTH_x = SOUTH_x;

	EAST_x = GRID_SIZE - 1;
	EAST_y = rand() % (GRID_SIZE - 2) + 1;

	if (EAST_y == GRID_SIZE - 1)
		EAST_y--;
	else if (EAST_y == 0)
		EAST_y++;
	else
		EAST_y = EAST_y;

	WEST_x = 0;
	WEST_y = rand() % (GRID_SIZE - 2) + 1;

	if (WEST_y == GRID_SIZE - 1)
		WEST_y--;
	else if (WEST_y == 0)
		WEST_y++;
	else
		WEST_y = WEST_y;

	GRID[NORTH_x][NORTH_y].reward = 1;

	GRID[SOUTH_x][SOUTH_y].reward = 1;

	GRID[EAST_x][EAST_y].reward = 1;

	GRID[WEST_x][WEST_y].reward = 1;
}

void Level::reset(sf::RenderWindow& window)
{
	for (auto cell : GRID)
	{
		cell->type = TILE_TYPE::EMPTY;
	}

	for (int i = 0; i < GRID_SIZE; i++)
	{
		for (int j = 0; j < GRID_SIZE; j++)
		{
			switch (GRID[i][j].type)
			{
			case TILE_TYPE::EMPTY:
				GRID[i][j].tile_sprite.setTexture(empty);
				break;

			default:
				GRID[i][j].tile_sprite.setTexture(empty);
				break;
			}
			GRID[i][j].tile_sprite.setPosition(sf::Vector2f((100.f * i) + 50, (100.f * j) + 50));
			window.draw(GRID[i][j].tile_sprite);
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
		generateExits();
		generateObstacles();
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
		generateExits();
		generateObstacles();
	}	
}

void Level::keepSize(sf::Clock* timer)
{
	if (timer->getElapsedTime().asMilliseconds() >= 50)
	{
		GRID_SIZE = GRID_SIZE;

		obstacles.clear();
		generateExits();
		generateObstacles();
	}
}

void Level::drawLevel(sf::RenderWindow& window)
{
	reset(window);

	checkExits();
	checkObstacles();

	for (int i = 0; i < GRID_SIZE; i++)
	{
		for (int j = 0; j < GRID_SIZE; j++)
		{
			if (i == agent_x && j == agent_y)
				GRID[i][j].type = TILE_TYPE::AGENT;

			switch (GRID[i][j].type)
			{
			case TILE_TYPE::EMPTY:
				GRID[i][j].tile_sprite.setTexture(empty);
				GRID[i][j].tile_sprite.setPosition(sf::Vector2f((100.f * i) + 50, (100.f * j) + 50));
				window.draw(GRID[i][j].tile_sprite);
				break;

			case TILE_TYPE::EXIT:
				GRID[i][j].tile_sprite.setTexture(exit);
				GRID[i][j].tile_sprite.setPosition(sf::Vector2f((100.f * i) + 50, (100.f * j) + 50));
				window.draw(GRID[i][j].tile_sprite);
				break;

			case TILE_TYPE::OBSTACLE:
				GRID[i][j].tile_sprite.setTexture(obstacle);;
				GRID[i][j].tile_sprite.setPosition(sf::Vector2f((100.f * i) + 50, (100.f * j) + 50));
				window.draw(GRID[i][j].tile_sprite);
				break;

			case TILE_TYPE::AGENT:
				std::cout << "agent found at :" << i << "   " << j << "\n\n" ;
				break;

			default:
				GRID[i][j].tile_sprite.setTexture(empty);
				GRID[i][j].tile_sprite.setPosition(sf::Vector2f((100.f * i) + 50, (100.f * j) + 50));
				window.draw(GRID[i][j].tile_sprite);
				break;
			}
		}
	}
}

int Level::getLevelSize()
{
	return GRID_SIZE;
}

int Level::getObstaclesNumber()
{
	return obstacles.size();
}

void Level::checkExits()
{
	for (int i = 0; i < GRID_SIZE; ++i)
	{
		for (int j = 0; j < GRID_SIZE; ++j)
		{
			auto cell = &GRID[i][j];
			if ((i == NORTH_x) && (j == NORTH_y))
			{
				cell->type = TILE_TYPE::EXIT;
				cell->reward = 1;
			}
			else if ((i == SOUTH_x) && (j == SOUTH_y))
			{
				cell->type = TILE_TYPE::EXIT;
				cell->reward = 1;
			}
			else if ((i == EAST_x) && (j == EAST_y))
			{
				cell->type = TILE_TYPE::EXIT;
				cell->reward = 1;
			}
			else if ((i == WEST_x) && (j == WEST_y))
			{
				cell->type = TILE_TYPE::EXIT;
				cell->reward = 1;
			}		
			else
				cell->type = TILE_TYPE::EMPTY;
		}
	}
}

void Level::checkObstacles()
{
	for (int i = 0; i < GRID_SIZE; ++i)
	{
		for (int j = 0; j < GRID_SIZE; ++j)
		{
			auto cell = &GRID[i][j];

			for (auto tile : obstacles)
			{
				if (tile.columnIndex == cell->columnIndex && tile.rowIndex == cell->rowIndex)
				{
					if (cell->type == TILE_TYPE::EMPTY || cell->type == TILE_TYPE::OBSTACLE)
					{
						cell->reward = -1;
						cell->type = TILE_TYPE::OBSTACLE;
					}
					else
						obstacles.pop_back();
				}
			}
		}
	}
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
				if (GRID[col][row].type == TILE_TYPE::EMPTY && GRID[col - 1][row].type == TILE_TYPE::EMPTY &&
					GRID[col+1][row].type == TILE_TYPE::EMPTY && GRID[col][row+1].type == TILE_TYPE::EMPTY &&
					GRID[col+1][row+1].type == TILE_TYPE::EMPTY && GRID[col+1][row-1].type == TILE_TYPE::EMPTY &&
					GRID[col-1][row+1].type == TILE_TYPE::EMPTY && GRID[col-1][row-1].type == TILE_TYPE::EMPTY &&
					GRID[col][row-1].type == TILE_TYPE::EMPTY && (col != 0 && col != GRID_SIZE - 1 && row != 0 && row != GRID_SIZE -1 ))
				{
					GRID[col][row].type = TILE_TYPE::OBSTACLE;
					obstacles.emplace_back(GRID[col][row]);
				}
			}
		}
	}
}

Tile* Level::GetTile(sf::Vector2i position, sf::RenderWindow& window)
{
	int tileColumn, tileRow;

	tileColumn = (position.x / 100);
	tileRow = (position.y / 100);

	return &GRID[tileColumn][tileRow];
}

Tile* Level::getTile(int x, int y)
{
	return &GRID[x][y];
}

void Level::setAgentPos(sf::Vector2i pos)
{
	agent_x = pos.x;
	agent_y = pos.y;
}

