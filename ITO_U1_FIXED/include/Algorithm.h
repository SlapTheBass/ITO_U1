#pragma once

#include "Agent.h"
#include "Level.h"

class Algorithm
{
public:
	Algorithm();
	~Algorithm();

	void seekPath(Level* level);
	void calculateRewards(Level* level);

private:
	std::vector<std::tuple<int, sf::Vector2i, float>> grids;
	Tile* _grid[10][10];
	bool canMove = true;
	int iterations;
	float gain;

	void FindR(Level* level);

	void GridInit(Level* level);

	void CheckTile(Tile* tile, Tile* agentTile);

	void HorizontalCheck(Tile* EAST, Tile* WEST, Tile* agentTile);
	void VerticalCheck(Tile* NORTH, Tile* SOUTH, Tile* agentTile);

	bool CanMoveWest(Tile* tile, int size);
	bool CanMoveEast(Tile* tile, int size);
	bool CanMoveNorth(Tile* tile, int size);
	bool CanMoveSouth(Tile* tile, int size);

	Tile* CompareTileRewards(Tile* tile1, Tile* tile2);

	float getGain();
};