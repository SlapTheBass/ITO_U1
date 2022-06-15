#pragma once

enum class DIRECTION {NORTH, SOUTH, EAST, WEST};

enum class TILE_TYPE {EMPTY, PLAYER, OBSTACLE, EXIT};

enum class APP_STATE {START, CLOSE};

enum class INPUT     {NONE, INC_SIZE, DEC_SIZE, RESET, QUIT};

struct Tile
{
	TILE_TYPE type = TILE_TYPE::EMPTY;
	int       x_pos = 0;
	int       y_pos = 0;
	float     reward = 0.0f;
};