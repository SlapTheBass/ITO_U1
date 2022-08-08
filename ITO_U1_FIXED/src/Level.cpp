#include "Level.h"

Level::Level()
{
	GRID_SIZE = MIN_SIZE;
	empty.loadFromFile("Utilities/spr_grass.png");

	initTiles();
}

Level::~Level()
{

}

int Level::getLevelSize()
{
	return GRID_SIZE;
}

int Level::getObstaclesNumber()
{
	int count = 0;

	for (int i = 0; i < GRID_SIZE; ++i)
	{
		for (int j = 0; j < GRID_SIZE; ++j)
		{
			auto tile = &GRID[i][j];

			if (tile->type == eOBSTACLE)
				count++;
		}
	}
	return count;
}

Tile* Level::GetTile(int x, int y)
{
	return &GRID[x][y];
}

Tile* Level::GetTile(sf::Vector2i position)
{
	int columnIndex, rowIndex;

	ResetColor();

	DBG(position.x);
	DBG(position.y);

	columnIndex = ((position.x - 576) / 50);
	rowIndex = ((position.y - 325) / 50);

	columnIndex = (columnIndex < 0) ? 0 : columnIndex;
	columnIndex = (columnIndex > GRID_SIZE - 1) ? (GRID_SIZE - 1) : columnIndex;

	rowIndex = (rowIndex < 0) ? 0 : rowIndex;
	rowIndex = (rowIndex > GRID_SIZE - 1) ? (GRID_SIZE - 1) : rowIndex;

	auto tile = &GRID[columnIndex][rowIndex];
	tile->tile_sprite.setColor(sf::Color(255, 255, 200, 180));

	return tile;
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
		resetAgent(timer);
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
			cell->type = eVOID;
			cell->status = eINACTIVE;
			cell->tile_sprite.setPosition(sf::Vector2f(i * 50 + 120, j * 50 + 50));
			cell->tile_sprite.setTexture(empty);
		}
	}

	for (int i = 0; i < GRID_SIZE; ++i)
	{
		for (int j = 0; j < GRID_SIZE; ++j)
		{
			auto cell = &GRID[i][j];
			cell->status = eACTIVE;
			cell->type = eEMPTY;
		}
	}

	generateExits();
	generateObstacles();
	generatePlayerTile();

	SpawnObjects();
}

void Level::reset()
{
	for (int i = 0; i < MAX_SIZE; ++i)
	{
		for (int j = 0; j < MAX_SIZE; ++j)
		{
			auto cell = &GRID[i][j];
			cell->type = eVOID;
			cell->status = eINACTIVE;
			cell->reward = 0;
		}
	}
}

void Level::incSize(sf::Clock* timer)
{
	if (timer->getElapsedTime().asMilliseconds() >= 50)
	{
		reset();

		GRID_SIZE++;

		if (GRID_SIZE > MAX_SIZE)
			GRID_SIZE = MAX_SIZE;

		for (int i = 0; i < GRID_SIZE; ++i)
		{
			for (int j = 0; j < GRID_SIZE; ++j)
			{
				auto tile = &GRID[i][j];
				tile->type = eEMPTY;
				tile->status = eACTIVE;
			}
		}

		_objects.clear();

		generateExits();
		generateObstacles();
		generatePlayerTile();

		SpawnObjects();
	}
}

void Level::decSize(sf::Clock* timer)
{
	if (timer->getElapsedTime().asMilliseconds() >= 50)
	{
		reset();

		GRID_SIZE--;

		if (GRID_SIZE < MIN_SIZE)
			GRID_SIZE = MIN_SIZE;

		for (int i = 0; i < GRID_SIZE; ++i)
		{
			for (int j = 0; j < GRID_SIZE; ++j)
			{
				auto tile = &GRID[i][j];
				tile->type = eEMPTY;
				tile->status = eACTIVE;
			}
		}

		_objects.clear();
		generateExits();
		generateObstacles();
		generatePlayerTile();

		SpawnObjects();
	}
}

void Level::resetAgent(sf::Clock* timer)
{
	if (timer->getElapsedTime().asMilliseconds() >= 50)
	{
		_agent->SetPosition(sf::Vector2f(start_x, start_y));
	}
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
	GRID[NORTH_x][NORTH_y].type = eEXIT;

	GRID[SOUTH_x][SOUTH_y].reward = 1;
	GRID[SOUTH_x][SOUTH_y].type = eEXIT;

	GRID[EAST_x][EAST_y].reward = 1;
	GRID[EAST_x][EAST_y].type = eEXIT;

	GRID[WEST_x][WEST_y].reward = 1;
	GRID[WEST_x][WEST_y].type = eEXIT;
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
					GRID[col][row].reward = -1;
				}
			}
		}
	}
}

void Level::generatePlayerTile()
{
	int col = rand() % (GRID_SIZE - 1);
	int row = rand() % (GRID_SIZE - 1);

	while ((GetTile(col, row)->type != eEMPTY) || col == GRID_SIZE - 1 || row == GRID_SIZE - 1 ||
		col == 0 || row == 0)
	{
		col = rand() % (GRID_SIZE - 1);
		row = rand() % (GRID_SIZE - 1);
	}

	start_x = col;
	start_y = row;

	auto tile = &GRID[col][row];
	tile->type = eAGENT;
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

	for (auto const& object : _objects)
	{
		object->Draw(window);
	}

	_agent->Draw(window);
}

void Level::ResetColor()
{
	for (int i = 0; i < GRID_SIZE; ++i)
	{
		for (int j = 0; j < GRID_SIZE; ++j)
		{
			auto tile = &GRID[i][j];
			tile->tile_sprite.setColor(sf::Color(255, 255, 255, 255));
		}
	}
}

void Level::SpawnObjects()
{
	std::unique_ptr<Object> object;

	for (int i = 0; i < GRID_SIZE; ++i)
	{
		for (int j = 0; j < GRID_SIZE; ++j)
		{
			auto tile = &GRID[i][j];
			switch (tile->type)
			{
			case eOBSTACLE:
				object = std::make_unique<Obstacle>(tile->tile_sprite.getPosition());
				_objects.push_back(std::move(object));
				break;

			case eEXIT:
				object = std::make_unique<Exit>(tile->tile_sprite.getPosition());
				_objects.push_back(std::move(object));
				break;

			case eAGENT:
				_agent = new Agent(tile->tile_sprite.getPosition());
				break;
			}
		}
	}
}