#include "Algorithm.h"

Algorithm::Algorithm()
{
}

Algorithm::~Algorithm()
{
}

void Algorithm::calculateRewards(Level& level)
{
	float temp = 0;

	FindR(level.getExits(), level);
	FindR(level.getObstacles(), level);

	for (int i = 0; i < level.getLevelSize(); ++i)
	{
		for (int j = 0; j < level.getLevelSize(); ++j)
		{
			for (int k = 0; k < grids.size(); ++k)
			{
				temp += grids[k][i][j].reward;
			}
			level.getTile(i, j)->reward = temp / grids.size();
		}
	}
	
}


void Algorithm::FindR(std::vector<Tile> vec)
{
	for (auto object : vec)
	{
		int size = level.getLevelSize();
		Tile** subGRID;
		subGRID = new Tile*[size];

		//SUBGRID init
		for (int i = 0; i < size; ++i)
		{
			subGRID[i] = new Tile[size];
		}

		
		for (int i = 0; i < size; ++i)
		{
			for (int j = 0; j < size; ++j)
			{
				subGRID[i][j].columnIndex = i;
				subGRID[i][j].rowIndex = j;
			}
		}

		for (int i = 0; i < size; ++i)
		{
			for (int j = 0; j < size; ++j)
			{
				if (object.columnIndex == i && object.rowIndex == j)
				{
					subGRID[i][j].type == object.type;
				}
				else
				{
					subGRID[i][j].type == TILE_TYPE::EMPTY;
				}
			}
		}

		float temp;

		for (int i = object.columnIndex; i < size; ++i)
		{
			if (object.columnIndex == i)
			{
				temp = object.reward;
				subGRID[i][object.rowIndex].reward = object.reward;
			}
			else
			{
				subGRID[i][object.rowIndex].reward = temp * 0.9;
				temp = subGRID[i][object.rowIndex].reward;
			}
		}

		for (int i = object.columnIndex; i > 0; --i)
		{
			if (object.columnIndex == i)
			{
				temp = object.reward;
				subGRID[i][object.rowIndex].reward = object.reward;
			}
			else
			{
				subGRID[i][object.rowIndex].reward = temp * 0.9;
				temp = subGRID[i][object.rowIndex].reward;
			}
		}

		for (int i = 0; i < size; ++i)
		{
			for (int j = object.rowIndex + 1; j < size; ++j)
			{
				subGRID[i][j].reward = subGRID[i][j - 1].reward * 0.9;
			}
		}

		for (int i = size; i > 0; --i)
		{
			for (int j = object.rowIndex - 1; j > 0; --j)
			{
				subGRID[i][j].reward = subGRID[i][j + 1].reward * 0.9;
			}
		}

		grids.emplace_back(subGRID);
	}
}