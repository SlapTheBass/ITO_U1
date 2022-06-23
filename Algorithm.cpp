#include "Algorithm.h"

Algorithm::Algorithm()
{
	exits.clear();
}

Algorithm::~Algorithm()
{
}

void Algorithm::calculaRewards(Level& level)
{
	for (int i = 0; i < level.getLevelSize(); ++i)
	{
		for (int j = 0; j < level.getLevelSize(); ++j)
		{
			auto node = level.getTile(i, j);
			if (node->type == TILE_TYPE::EXIT)
			{
				exits.push_back(node);
			}
		}
	}

	float temp = 1;
	for (int i = exits[0]->columnIndex; i < level.getLevelSize(); ++i)
	{
		for (int j = exits[0]->rowIndex; j < level.getLevelSize(); ++j)
		{
			auto cell = level.getTile(i, j);
			cell->reward = temp * 0.9;
			temp = cell->reward;
		}
	}
	
}
