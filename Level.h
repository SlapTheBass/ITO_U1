#pragma once

#include "PCH.h"
#include "TextureManager.h"
#include "SoundManager.h"
#include "Obstacle.h"
#include "Utilities.h"
#include <vector>


class Level
{
public:
	Level();
	~Level();

	void initTiles();

private:
	static const int    MAX_SIZE = 10;
	static const int    MIN_SIZE = 3;
	int    GRID_SIZE;

	Tile** GRID;

	std::vector<Obstacle> obstacles;
};

