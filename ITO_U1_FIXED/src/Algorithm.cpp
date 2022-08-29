#include "Algorithm.h"

Algorithm::Algorithm()
{

}

Algorithm::~Algorithm()
{

}


void Algorithm::FindR(Level* level)
{
	grids.clear();
	int index = 1;

	std::vector<Tile*> exits = level->checkExits();  //get exits
	std::vector<Tile*> obstacles = level->checkObstacles();//  get obstacles

	std::vector<Tile*> objects;

	objects.insert(objects.end(), exits.begin(), exits.end());
	objects.insert(objects.end(), obstacles.begin(), obstacles.end()); //merge exits and obstacles into one container of general objects

	int gridSize = level->getLevelSize();

	for (auto object : objects) //for every single exit and obstacle in objects container make subgrid and calculate rewards for every tile
	{						  
		Tile subGRID[10][10];
		//SUBGRID init

		for (int i = 0; i < level->getLevelSize(); ++i)
		{
			for (int j = 0; j < level->getLevelSize(); ++j)
			{
				subGRID[i][j].columnIndex = i;
				subGRID[i][j].rowIndex = j;

				if (object->columnIndex == i && object->rowIndex == j)
				{
					subGRID[i][j] = *object;
				}
				else
				{
					subGRID[i][j].type == eEMPTY;
				}
			}
		}

		float temp;

		for (int i = object->columnIndex; i < gridSize; ++i) //calculate rewards of tiles on the objects' right side
		{
			if (object->columnIndex == i)
			{
				subGRID[i][object->rowIndex].reward = object->reward;
				temp = object->reward;
			}
			else
			{
				subGRID[i][object->rowIndex].reward = temp * discount;
				temp = subGRID[i][object->rowIndex].reward;
			}
		}

		for (int i = object->columnIndex; i >= 0; --i) //calculate rewards of tiles on the objects' left side
		{
			if (object->columnIndex == i)
			{
				subGRID[i][object->rowIndex].reward = object->reward;
				temp = object->reward;
			}
			else
			{
				subGRID[i][object->rowIndex].reward = temp * discount;
				temp = subGRID[i][object->rowIndex].reward;
			}
		}

		for (int i = 0; i < gridSize; ++i) //take row in which object is placed and calculate rewards downside
		{
			for (int j = object->rowIndex + 1; j < gridSize; ++j)
			{
				subGRID[i][j].reward = (subGRID[i][j - 1].reward * discount);
			}
		}
		
		for (int i = 0; i < gridSize; ++i)  //take row in which object is placed and calculate rewards upside
		{
			for (int j = object->rowIndex - 1; j >= 0; --j)
			{
				subGRID[i][j].reward = (subGRID[i][j + 1].reward * discount);
			}
		}


		for (int i = 0; i < level->getLevelSize(); ++i) //for all subgrid make tuple including tile position and its' reward
		{
			for (int j = 0; j < level->getLevelSize(); ++j)
			{
				auto data = std::make_tuple(index, sf::Vector2i(i, j), subGRID[i][j].reward);
				grids.push_back(data); //push tuple into container
			}
		}
		index++;
	}

	iterations = index; //iterations is actually number of objects on main grid
	objects.clear();
}

void Algorithm::calculateRewards(Level* level)
{
	float temp = 0;

	FindR(level);

	int gridSize = level->getLevelSize();

	GridInit(level);

	for (auto element : grids) //for every tuple in container named grids
	{
		for (int i = 0; i < gridSize; ++i)
		{
			for (int j = 0; j < gridSize; ++j)
			{
				if (std::get<1>(element).x == i && std::get<1>(element).y == j) //check if saved row and column indexes are fine
				{
					if (_grid[i][j]->type == eEXIT)
					{
						_grid[i][j]->reward = 1; //const reward for exit
					}
					else if (_grid[i][j]->type == eOBSTACLE)
					{
						_grid[i][j]->reward = -1; //const reward for obstacle
					}
					else
					{
						_grid[i][j]->reward += std::get<2>(element); //rest of rewards are calculed - for every empty tile add it's reward value from every subgrid
					}
				}
			}
		}
	}

	for (int i = 0; i < gridSize; ++i)
	{
		for (int j = 0; j < gridSize; ++j)
		{
			if (_grid[i][j]->type != eEXIT && _grid[i][j]->type != eOBSTACLE)
			{
				_grid[i][j]->reward = (_grid[i][j]->reward / iterations); //for every empty tile divide summed reward by number of subgrids
			}
		}
	}
}

void Algorithm::seekPath(Level* level)
{
	//calculateRewards(level);

	auto agentTile = level->GetAgentTile();
	int gridSize = level->getLevelSize();

	/*definition tiles surrounding agent*/
	Tile* EAST;
	Tile* WEST;
	Tile* SOUTH;
	Tile* NORTH;
	EAST = _grid[agentTile->columnIndex + 1][agentTile->rowIndex];
	WEST = _grid[agentTile->columnIndex - 1][agentTile->rowIndex];
	NORTH = _grid[agentTile->columnIndex][agentTile->rowIndex - 1];
	SOUTH = _grid[agentTile->columnIndex][agentTile->rowIndex + 1];

	/*check if  agent is  at  one of level borders*/
	eastBorder = CanMoveEast(agentTile, gridSize);
	westBorder = CanMoveWest(agentTile, gridSize);
	northBorder = CanMoveNorth(agentTile, gridSize);
	southBorder = CanMoveSouth(agentTile, gridSize);

	int movesLeft = level->GetSteps();

	if (movesLeft == 0)
	{
		canMove = false;
	}

	if (canMove)
	{
		if (eastBorder == false)
		{
			HorizontalBorderCheck(WEST, SOUTH, NORTH, agentTile);
		}
		else if (westBorder == false)
		{
			HorizontalBorderCheck(EAST, SOUTH, NORTH, agentTile);
		}
		else if (northBorder == false)
		{
			VerticalBorderCheck(SOUTH, WEST, EAST, agentTile);
		}
		else if (southBorder == false)
		{
			VerticalBorderCheck(NORTH, WEST, EAST, agentTile);
		}
		else
		{
			horizontal = (EAST->reward > WEST->reward ? EAST->reward : WEST->reward);
			vertical = (NORTH->reward > SOUTH->reward ? NORTH->reward : SOUTH->reward);

			if (horizontal > vertical)
			{
				HorizontalCheck(EAST, WEST, agentTile);
			}
			else
			{
				VerticalCheck(NORTH, SOUTH, agentTile);
			}
		}
	}
}

void Algorithm::GridInit(Level* level)
{
	
	for (int i = 0; i < level->getLevelSize(); ++i) //copy main grid into helper grid
	{
		for (int j = 0; j < level->getLevelSize(); ++j)
		{
			_grid[i][j] = level->GetTile(i, j);
		}
	}
}

void Algorithm::CheckTile(Tile* tile, Tile* agentTile)
{
	if (tile->type == eEXIT)
	{
		tile->reward += 1;
		agentTile->columnIndex = tile->columnIndex;
		agentTile->rowIndex = tile->rowIndex;
		agentTile->type = tempType;
		tempType = tile->type;
		tile->type = eAGENT;
		canMove = false;
		exitFound = true;
		//path = ACTION::EAST;
	}
	else if (tile->type == eEMPTY)
	{
		tile->reward += 0.3;
		agentTile->columnIndex = tile->columnIndex;
		agentTile->rowIndex = tile->rowIndex;
		agentTile->type = tempType;
		tempType = tile->type;
		tile->type = eAGENT;
		exitFound = false;
		//path = ACTION::EAST;
	}
	else
	{
		tile->reward += -1;
		agentTile->columnIndex = tile->columnIndex;
		agentTile->rowIndex = tile->rowIndex;
		agentTile->type = tempType;
		tempType = tile->type;
		tile->type = eAGENT;
		exitFound = false;
		//path = ACTION::EAST;
	}

	reset = false;
}

void Algorithm::HorizontalCheck(Tile* EAST, Tile* WEST, Tile* agentTile)
{
	if (EAST->reward > WEST->reward)
	{
		CheckTile(EAST, agentTile);
	}
	else
	{
		CheckTile(WEST, agentTile);
	}
}

void Algorithm::VerticalCheck(Tile* NORTH, Tile* SOUTH, Tile* agentTile)
{
	if (NORTH->reward > SOUTH->reward)
	{
		CheckTile(NORTH, agentTile);
	}
	else
	{
		CheckTile(SOUTH, agentTile);
	}
}

bool Algorithm::CanMoveEast(Tile* tile, int size)
{
	bool retv = true;

	if (tile->columnIndex == size - 1)
	{
		retv = false;
	}

	return retv;
}

bool Algorithm::CanMoveWest(Tile* tile, int size)
{
	bool retv = true;

	if (tile->columnIndex == 0)
	{
		retv = false;
	}

	return retv;
}

bool Algorithm::CanMoveNorth(Tile* tile, int size)
{
	bool retv = true;

	if (tile->rowIndex == 0)
	{
		retv = false;
	}

	return retv;
}

bool Algorithm::CanMoveSouth(Tile* tile, int size)
{
	bool retv = true;

	if (tile->rowIndex == size - 1)
	{
		retv = false;
	}

	return retv;
}

void Algorithm::HorizontalBorderCheck(Tile* tile1, Tile* tile2, Tile* tile3, Tile* agentTile)
{
	horizontal = tile1->reward;

	if (northBorder == false) //check if agent is in the corner
	{
		vertical = tile2->reward;
	}
	else if (southBorder == false)
	{
		vertical = tile3->reward;
	}
	else
	{
		vertical = (tile3->reward > tile2->reward ? tile3->reward : tile2->reward);
	}

	if (horizontal > vertical)
	{
		CheckTile(tile1, agentTile);  //if agent is on horizontal border and horizontal reward is higher it means he can perform move only in one direction
	}
	else
	{
		if (northBorder == false) //if vertical reward is higher and agent is in the corner perforrm check in one direction
		{
			CheckTile(tile2, agentTile);
		}
		else if (southBorder == false) //if vertical reward is higher and agent is in the corner perforrm check in one direction
		{
			CheckTile(tile3, agentTile);
		}
		else //if agent is not  in the corner perform basic vertical check
		{
			VerticalCheck(tile3, tile2, agentTile);
		}
	}
}

void Algorithm::VerticalBorderCheck(Tile* tile1, Tile* tile2, Tile* tile3, Tile* agentTile)
{
	vertical = tile1->reward;

	if (eastBorder == false) //check if agent is in the corner
	{
		horizontal = tile2->reward;
	}
	else if (westBorder == false)
	{
		horizontal = tile3->reward;
	}
	else
	{
		horizontal = (tile3->reward > tile2->reward ? tile3->reward : tile2->reward);
	}

	if (horizontal > vertical)
	{
		if (eastBorder == false) //if horizontal rewartd is higher and agent is in the corner perform check in one direction
		{
			CheckTile(tile2, agentTile);
		}
		if (westBorder == false) //if horizontal rewartd is higher and agent is in the corner perform check in one direction
		{
			CheckTile(tile3, agentTile);
		}
		else // if agent is not in the corner perform basci horizontal check
		{
			HorizontalCheck(tile3, tile2, agentTile);
		}
	}
	else
	{
		CheckTile(tile1, agentTile); //if agent is on vertical border and horizontal reward is higher it means he can perform move only in one direction
	}
}

void Algorithm::Reset()
{
	tempType = eEMPTY;
	canMove = true;
	exitFound = false;
}

bool Algorithm::CanMove()
{
	return canMove;
}

bool Algorithm::ExitFound()
{
	return  exitFound;
}