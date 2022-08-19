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
	int index = 0;

	std::vector<Tile*> exits = level->checkExits();
	std::vector<Tile*> obstacles = level->checkObstacles();

	std::vector<Tile*> objects;

	objects.insert(objects.end(), exits.begin(), exits.end());
	objects.insert(objects.end(), obstacles.begin(), obstacles.end());

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

		for (int i = object->columnIndex; i < agentTile->columnIndex; ++i)
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

		for (int i = object->columnIndex; i >= agentTile->columnIndex; --i)
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

		for (int i = 0; i <= agentTile->columnIndex; ++i)
		{
			for (int j = object->rowIndex + 1; j <= agentTile->rowIndex; ++j)
			{
				subGRID[i][j].reward = (subGRID[i][j - 1].reward * 0.9) - 0.04;
			}
		}

		for (int i = level->getLevelSize() - 1; i >= agentTile->columnIndex; --i)
		{
			for (int j = object->rowIndex - 1; j >= agentTile->rowIndex; --j)
			{
				subGRID[i][j].reward = (subGRID[i][j + 1].reward * 1.111);
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
	calculateRewards(level);

	auto agentTile = level->GetAgentTile();

	Tile* EAST, * WEST, * NORTH, * SOUTH;
	EAST = _grid[agentTile->columnIndex - 1][agentTile->rowIndex];
	WEST = _grid[agentTile->columnIndex + 1][agentTile->rowIndex];
	NORTH = _grid[agentTile->columnIndex][agentTile->rowIndex - 1];
	SOUTH = _grid[agentTile->columnIndex][agentTile->rowIndex + 1];

	if (canMove)
	{
		if ((agentTile->columnIndex == level->getLevelSize() - 1) || (agentTile->columnIndex == 0))
		{
			canMove = false;
		}
		else if ((agentTile->rowIndex == level->getLevelSize() - 1) || (agentTile->rowIndex == 0))
		{
			canMove = false;
		}
		else
		{
			float horizontal = (EAST->reward > WEST->reward ? EAST->reward : WEST->reward);
			float vertical = (NORTH->reward > SOUTH->reward ? NORTH->reward : SOUTH->reward);

			if (horizontal > vertical)
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
			else
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
		gain += 1;
		tile->reward += gain;
		agentTile->columnIndex = tile->columnIndex;
		agentTile->rowIndex = tile->rowIndex;
		agentTile->type = eEMPTY;
		tile->type = eAGENT;
		//path = ACTION::EAST;
	}
	else if (tile->type == eEMPTY)
	{
		gain += 0.01;
		tile->reward += gain;
		agentTile->columnIndex = tile->columnIndex;
		agentTile->rowIndex = tile->rowIndex;
		agentTile->type = eEMPTY;
		tile->type = eAGENT;
		//path = ACTION::EAST;
	}
	else
	{
		gain -= 1;
		tile->reward += gain;
		agentTile->columnIndex = tile->columnIndex;
		agentTile->rowIndex = tile->rowIndex;
		agentTile->type = eEMPTY;
		tile->type = eAGENT;
		//path = ACTION::EAST;
	}
}