#pragma once

#include "PCH.h"
#include "Level.h"

class Algorithm
{
public:
	Algorithm();
	~Algorithm();

	void calculaRewards(Level& level);

private:
	std::vector<Tile*> exits;
};

