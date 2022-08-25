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

	std::vector<Tile*> exits = level->checkExits();
	std::vector<Tile*> obstacles = level->checkObstacles();

	std::vector<Tile*> objects;

	objects.insert(objects.end(), exits.begin(), exits.end());
	objects.insert(objects.end(), obstacles.begin(), obstacles.end());

	int gridSize = level->getLevelSize();

	for (auto object : objects)
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
		auto agentTile = level->GetAgentTile();

		for (int i = object->columnIndex; i < gridSize; ++i)
		{
			if (object->columnIndex == i)
			{
				subGRID[i][object->rowIndex].reward = object->reward;
				temp = object->reward;
			}
			else
			{
				subGRID[i][object->rowIndex].reward = temp * 0.9;
				temp = subGRID[i][object->rowIndex].reward;
			}
		}

		for (int i = object->columnIndex; i >= 0; --i)
		{
			if (object->columnIndex == i)
			{
				subGRID[i][object->rowIndex].reward = object->reward;
				temp = object->reward;
			}
			else
			{
				subGRID[i][object->rowIndex].reward = temp * 0.9;
				temp = subGRID[i][object->rowIndex].reward;
			}
		}

		for (int i = 0; i < gridSize; ++i)
		{
			for (int j = object->rowIndex + 1; j < gridSize; ++j)
			{
				subGRID[i][j].reward = (subGRID[i][j - 1].reward * 0.9);
			}
		}
		
		for (int i = 0; i < gridSize; ++i)
		{
			for (int j = object->rowIndex - 1; j >= 0; --j)
			{
				subGRID[i][j].reward = (subGRID[i][j + 1].reward * 0.9);
			}
		}


		for (int i = 0; i < level->getLevelSize(); ++i)
		{
			for (int j = 0; j < level->getLevelSize(); ++j)
			{
				auto data = std::make_tuple(index, sf::Vector2i(i, j), subGRID[i][j].reward);
				grids.push_back(data);
			}
		}
		index++;
	}

	iterations = index;
	objects.clear();
}

void Algorithm::calculateRewards(Level* level)
{
	float temp = 0;

	FindR(level);

	int gridSize = level->getLevelSize();

	GridInit(level);

	for (auto element : grids)
	{
		for (int i = 0; i < gridSize; ++i)
		{
			for (int j = 0; j < gridSize; ++j)
			{
				if (std::get<1>(element).x == i && std::get<1>(element).y == j)
				{
					if (_grid[i][j]->type == eEXIT)
					{
						_grid[i][j]->reward = 1;
					}
					else if (_grid[i][j]->type == eOBSTACLE)
					{
						_grid[i][j]->reward = -1;
					}
					else
					{
						_grid[i][j]->reward += std::get<2>(element);
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
				_grid[i][j]->reward = (_grid[i][j]->reward / iterations);
			}
		}
	}
}

void Algorithm::seekPath(Level* level)
{
	//calculateRewards(level);

	auto agentTile = level->GetAgentTile();
	int gridSize = level->getLevelSize();

	Tile* EAST, * WEST, * NORTH, * SOUTH;
	EAST = _grid[agentTile->columnIndex + 1][agentTile->rowIndex];
	WEST = _grid[agentTile->columnIndex - 1][agentTile->rowIndex];
	NORTH = _grid[agentTile->columnIndex][agentTile->rowIndex - 1];
	SOUTH = _grid[agentTile->columnIndex][agentTile->rowIndex + 1];

	bool eastBorder = CanMoveEast(agentTile, gridSize);
	bool westBorder = CanMoveWest(agentTile, gridSize);
	bool northBorder = CanMoveNorth(agentTile, gridSize);
	bool southBorder = CanMoveSouth(agentTile, gridSize);

	canMove = eastBorder || westBorder || northBorder || southBorder;

	float horizontal, vertical;

	if (canMove)
	{
		if (eastBorder == false)
		{
			horizontal = WEST->reward;

			if (northBorder == false)
			{
				vertical = SOUTH->reward;
			}
			else if (southBorder == false)
			{
				vertical = NORTH->reward;
			}
			else
			{
				vertical = (NORTH->reward > SOUTH->reward ? NORTH->reward : SOUTH->reward);
			}

			if (horizontal > vertical)
			{
				HorizontalCheck(WEST, WEST, agentTile);
			}
			else
			{
				if (northBorder == false)
				{
					CheckTile(SOUTH, agentTile);
				}
				else if (southBorder == false)
				{
					CheckTile(NORTH, agentTile);
				}
				else
				{
					VerticalCheck(NORTH, SOUTH, agentTile);
				}
			}
		}
		else if (westBorder == false)
		{
			horizontal = EAST->reward;
			
			if (northBorder == false)
			{
				vertical = SOUTH->reward;
			}
			else if (southBorder == false)
			{
				vertical = NORTH->reward;
			}
			else
			{
				vertical = (NORTH->reward > SOUTH->reward ? NORTH->reward : SOUTH->reward);
			}

			if (horizontal > vertical)
			{
				HorizontalCheck(EAST, EAST, agentTile);
			}
			else
			{
				if (northBorder == false)
				{
					CheckTile(SOUTH, agentTile);
				}
				else if (southBorder == false)
				{
					CheckTile(NORTH, agentTile);
				}
				else
				{
					VerticalCheck(NORTH, SOUTH, agentTile);
				}
			}
		}
		else if (northBorder == false)
		{
			vertical = SOUTH->reward;

			if (eastBorder == false)
			{
				horizontal = WEST->reward;
			}
			else if (westBorder == false)
			{
				horizontal = EAST->reward;
			}
			else
			{
				horizontal = (EAST->reward > WEST->reward ? EAST->reward : WEST->reward);
			}

			if (horizontal > vertical)
			{
				if (eastBorder == false)
				{
					CheckTile(WEST, agentTile);
				}
				if (westBorder == false)
				{
					CheckTile(EAST, agentTile);
				}
				else
				{
					HorizontalCheck(EAST, WEST, agentTile);
				}
			}
			else
			{
				VerticalCheck(SOUTH, SOUTH, agentTile);
			}
		}
		else if (southBorder == false)
		{
			vertical = NORTH->reward;

			if (eastBorder == false)
			{
				horizontal = WEST->reward;
			}
			else if (westBorder == false)
			{
				horizontal = EAST->reward;
			}
			else
			{
				horizontal = (EAST->reward > WEST->reward ? EAST->reward : WEST->reward);
			}

			if (horizontal > vertical)
			{
				if (eastBorder == false)
				{
					CheckTile(WEST, agentTile);
				}
				if (westBorder == false)
				{
					CheckTile(EAST, agentTile);
				}
				else
				{
					HorizontalCheck(EAST, WEST, agentTile);
				}
			}
			else
			{
				VerticalCheck(NORTH, NORTH, agentTile);
			}
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
	
	for (int i = 0; i < level->getLevelSize(); ++i)
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
		agentTile->type = eEMPTY;
		tile->type = eAGENT;
		//path = ACTION::EAST;
	}
	else if (tile->type == eEMPTY)
	{
		tile->reward += 0.3;
		agentTile->columnIndex = tile->columnIndex;
		agentTile->rowIndex = tile->rowIndex;
		agentTile->type = eEMPTY;
		tile->type = eAGENT;
		//path = ACTION::EAST;
	}
	else
	{
		tile->reward += -1;
		agentTile->columnIndex = tile->columnIndex;
		agentTile->rowIndex = tile->rowIndex;
		agentTile->type = eEMPTY;
		tile->type = eAGENT;
		//path = ACTION::EAST;
	}
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
