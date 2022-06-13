#pragma once

#include "TextureManager.h"
#include "SoundManager.h"
#include "Obstacle.h"
#include "Utilities.h"
#include <vector>

struct Tile
{
	TILE_TYPE type   = TILE_TYPE::EMPTY;
	int       x_pos  = 0;
	int       y_pos  = 0;
	float     reward = 0.0f;
};

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

