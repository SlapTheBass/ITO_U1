#pragma once

#include "PCH.h"
#include "Level.h"

class Algorithm
{
public:
	Algorithm();
	~Algorithm();

	void calculateRewards(Level& level);
	void FindR(std::vector<Tile> vec, Level& level);

private:
	std::vector<Tile**> grids;
};

