#include "Level.h"

Level::Level()
{
	GRID_SIZE = MIN_SIZE;  //declare level size at starting point
	empty.loadFromFile("Utilities/spr_grass.png");  //texture of empty tile

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
				count++; //increase  count if obstacle  is on tile
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

	columnIndex = ((position.x - 576) / 50); //column and row  indexes are calculated  from mouse position
	rowIndex = ((position.y - 325) / 50);

	columnIndex = (columnIndex < 0) ? 0 : columnIndex; //prevent getting  tile  not in  the range
	columnIndex = (columnIndex > GRID_SIZE - 1) ? (GRID_SIZE - 1) : columnIndex;

	rowIndex = (rowIndex < 0) ? 0 : rowIndex;
	rowIndex = (rowIndex > GRID_SIZE - 1) ? (GRID_SIZE - 1) : rowIndex;

	auto tile = &GRID[columnIndex][rowIndex];
	tile->tile_sprite.setColor(sf::Color(255, 255, 200, 180));  //mark tile with darker  colour

	return tile;
}

void Level::Update(Input& input, sf::Clock* timer)
{
	if (input.pressedKey() == eINC_SIZE) //SHIFT detected
	{
		incSize(timer);
		stepsLeft = ((rand() % 2) + 1) * GRID_SIZE;
		tempSteps = stepsLeft;
		timer->restart();
	}
	else if (input.pressedKey() == eDEC_SIZE)  //CTRL detected
	{
		decSize(timer);
		stepsLeft = ((rand() % 2) + 1) * GRID_SIZE;
		tempSteps = stepsLeft;
		timer->restart();
	}
	else if (input.pressedKey() == eRESET)  //R detected
	{
		resetAgent(timer);
		stepsLeft = tempSteps;
		timer->restart();
	}
}

void Level::initTiles()
{
	for (int i = 0; i < MAX_SIZE; ++i)    //initialize whole grid of maximum size
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

	for (int i = 0; i < GRID_SIZE; ++i)  //activate only tiles included in actual grid size
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
	generateAgentTile();

	SpawnObjects();

	stepsLeft = (rand() % 2 + 1) * GRID_SIZE;
	tempSteps = stepsLeft;
}

void Level::reset()
{
	for (int i = 0; i < MAX_SIZE; ++i) //reset whole grid
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

		GRID_SIZE++; //increase level size

		if (GRID_SIZE > MAX_SIZE)
			GRID_SIZE = MAX_SIZE; //level size can not be greater than declared maximum size

		for (int i = 0; i < GRID_SIZE; ++i)
		{
			for (int j = 0; j < GRID_SIZE; ++j) // activate tiles included in grid of actual size
			{
				auto tile = &GRID[i][j];
				tile->type = eEMPTY;
				tile->status = eACTIVE;
			}
		}

		_objects.clear();

		generateExits();
		generateObstacles();
		generateAgentTile();

		SpawnObjects();
	}
}

void Level::decSize(sf::Clock* timer)
{
	if (timer->getElapsedTime().asMilliseconds() >= 50)
	{
		reset();

		GRID_SIZE--; //decrease level size

		if (GRID_SIZE < MIN_SIZE)
			GRID_SIZE = MIN_SIZE; //level size can not be less than declared minimum grid size

		for (int i = 0; i < GRID_SIZE; ++i)
		{
			for (int j = 0; j < GRID_SIZE; ++j) // activate tiles included in grid of actual size
			{
				auto tile = &GRID[i][j];
				tile->type = eEMPTY;
				tile->status = eACTIVE;
			}
		}

		_objects.clear();
		generateExits();
		generateObstacles();
		generateAgentTile();

		SpawnObjects();
	}
}

void Level::resetAgent(sf::Clock* timer)
{
	if (timer->getElapsedTime().asMilliseconds() >= 50)
	{
		ClearAgent(); //destroy agent

		for (auto exit : mg_exits) //restore exits - it prevents from getting empty tile after destroying agent standing on exit tile
		{
			exit->type = eEXIT;
		}

		for (auto obstacle : mg_obstacles) //restore obstacles - it prevents from getting empty tile after destroying agent standing on obstacle tile
		{
			obstacle->type = eOBSTACLE;
		}

		generateAgentTile();
		SpawnAgent();
	}
}


void Level::generateExits()
{
	mg_exits.clear();

	NORTH_x = rand() % GRID_SIZE; //randomize  x  position of north exit
	NORTH_y = 0; //y position of  north exit  has  to be const

	if (NORTH_x == GRID_SIZE - 1)  //prevent of getting north  exit in corner
		NORTH_x--;
	else if (NORTH_x == 0)
		NORTH_x++;
	else
		NORTH_x = NORTH_x;

	SOUTH_x = rand() % GRID_SIZE; //randomize x position  of south exit
	SOUTH_y = GRID_SIZE - 1; //y position of south exit has  to be const

	if (SOUTH_x == GRID_SIZE - 1)  //prevent of getting south  exit  in  corner
		SOUTH_x--;
	else if (SOUTH_x == 0)
		SOUTH_x++;
	else
		SOUTH_x = SOUTH_x;

	EAST_x = GRID_SIZE - 1; //x  position of east exit has to be const
	EAST_y = rand() % (GRID_SIZE - 2) + 1; //ranodmize y position of east exit

	if (EAST_y == GRID_SIZE - 1) //prevent of getting east exit in corner
		EAST_y--;
	else if (EAST_y == 0)
		EAST_y++;
	else
		EAST_y = EAST_y;

	WEST_x = 0; //x  position of west exit  has to be const
	WEST_y = rand() % (GRID_SIZE - 2) + 1; //randomize y  position of west exit

	if (WEST_y == GRID_SIZE - 1)  //prevent of getting  west exit in corner
		WEST_y--;
	else if (WEST_y == 0)
		WEST_y++;
	else
		WEST_y = WEST_y;

	GRID[NORTH_x][NORTH_y].reward = 1;
	GRID[NORTH_x][NORTH_y].type = eEXIT;
	mg_exits.push_back(&GRID[NORTH_x][NORTH_y]);  //place exits on level and push tiles to  container

	GRID[SOUTH_x][SOUTH_y].reward = 1;
	GRID[SOUTH_x][SOUTH_y].type = eEXIT;
	mg_exits.push_back(&GRID[SOUTH_x][SOUTH_y]);

	GRID[EAST_x][EAST_y].reward = 1;
	GRID[EAST_x][EAST_y].type = eEXIT;
	mg_exits.push_back(&GRID[EAST_x][EAST_y]);

	GRID[WEST_x][WEST_y].reward = 1;
	GRID[WEST_x][WEST_y].type = eEXIT;
	mg_exits.push_back(&GRID[WEST_x][WEST_y]);
}

void Level::generateObstacles()
{
	mg_obstacles.clear();

	for (int i = 0; i < 2 * GRID_SIZE - 5; ++i) //generate specific  ammount of obstacles
	{
		int col = rand() % GRID_SIZE; //randomize obstacle   position
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
				{   //if tile on generated position is empty, tiles around it are empty and tile is not at level border -> generate obstacle 
					GRID[col][row].type = eOBSTACLE;
					GRID[col][row].reward = -1;
					mg_obstacles.push_back(&GRID[col][row]); //place obstacle  in container
				}
			}
		}
	}
}

void Level::generateAgentTile()
{
	for (int i = 0; i < GRID_SIZE; ++i)
	{
		for (int j = 0; j < GRID_SIZE; ++j)  //clear actual agent position
		{
			auto tile = &GRID[i][j];

			if (tile->type == eAGENT)
			{
				tile->type = eEMPTY;
			}
		}
	}

	int col = rand() % (GRID_SIZE - 1); //randomize  new agent position
	int row = rand() % (GRID_SIZE - 1);

	while ((GetTile(col, row)->type != eEMPTY) || col == GRID_SIZE - 1 || row == GRID_SIZE - 1 ||
		col == 0 || row == 0)
	{  //keep  generating position until tile will be empty   and will not be  placed at level border
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

			window->draw(tile->tile_sprite); //draw empty  tiles
		}
	}

	for (auto const& object : _objects)
	{
		object->Draw(window); // draw objects
	}

	_agent->Draw(window);  //draw agent
}

void Level::ResetColor()
{
	for (int i = 0; i < GRID_SIZE; ++i)
	{
		for (int j = 0; j < GRID_SIZE; ++j)
		{
			auto tile = &GRID[i][j];
			tile->tile_sprite.setColor(sf::Color(255, 255, 255, 255)); //reset colour of tiles that are not  pointed any more
		}
	}
}

void Level::SpawnObjects()
{
	std::unique_ptr<Object> object; //polimorphism usage

	for (int i = 0; i < GRID_SIZE; ++i)
	{
		for (int j = 0; j < GRID_SIZE; ++j)
		{
			auto tile = &GRID[i][j];
			switch (tile->type) //spawn objects that are associated with tile  types
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

std::vector<Tile*> Level::checkExits()
{
	std::vector<Tile*> exits;

	for (int i = 0; i < GRID_SIZE; ++i) //seek whole grid  for exits 
	{
		for (int j = 0; j < GRID_SIZE; ++j)
		{
			auto tile = &GRID[i][j];

			if (tile->type == eEXIT)
			{
				exits.emplace_back(tile);
			}
		}
	}

	return exits; 
}

std::vector<Tile*> Level::checkObstacles()
{
	std::vector<Tile*> obstacles;

	for (int i = 0; i < GRID_SIZE; ++i) //seek whole  grid   for obstacles
	{
		for (int j = 0; j < GRID_SIZE; ++j)
		{
			auto tile = &GRID[i][j];

			if (tile->type == eOBSTACLE)
			{
				obstacles.emplace_back(tile);
			}
		}
	}

	return obstacles;

}

Tile* Level::GetAgentTile()
{
	Tile* Agent = nullptr;

	for (int i = 0; i < GRID_SIZE; ++i)  //seek whole grid for agent
	{
		for (int j = 0; j < GRID_SIZE; ++j)
		{
			auto tile = &GRID[i][j];

			if (tile->type == eAGENT)
			{
				Agent = tile;
				Agent->columnIndex = i;
				Agent->rowIndex = j;
			}
		}
	}

	return Agent;
}

void Level::ClearAgent()
{
	_agent->~Agent();
}

void Level::SpawnAgent()
{
	for (int i = 0; i < GRID_SIZE; ++i) //spawn agent at Agent type tile
	{
		for (int j = 0; j < GRID_SIZE; ++j)
		{
			auto tile = &GRID[i][j];

			if (tile->type == eAGENT)
			{
				_agent = new Agent(tile->tile_sprite.getPosition());
			}
		}
	}
}

int Level::GetSteps()
{
	return stepsLeft;
}

void Level::DecreaseSteps()
{
	stepsLeft--;

	if (stepsLeft <= 0)
		stepsLeft = 0;
}
