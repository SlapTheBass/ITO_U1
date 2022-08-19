#pragma once

#include "Agent.h"
#include "Level.h"

class Algorithm
{
public:
	Algorithm();
	~Algorithm();

	void seekPath(Level* level);

private:
	std::vector<std::tuple<int, sf::Vector2i, float>> grids;
	Tile* _grid[10][10];
	bool canMove = true;
	int iterations;
	float gain;

	void calculateRewards(Level* level);

	void FindR(Level* level);

	void GridInit(Level* level);

	void CheckTile(Tile* tile, Tile* agentTile);

	float getGain();
};