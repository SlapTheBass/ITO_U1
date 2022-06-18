#pragma once

#include "PCH.h"
#include "TextureManager.h"
#include "SoundManager.h"
#include "Utilities.h"
#include <vector>

struct Tile
{
	TILE_TYPE   type        = TILE_TYPE::EMPTY;
	float       x_pos       = 0;
	float       y_pos       = 0;
	float       reward      = 0.0f;
	int         columnIndex = 0;
	int         rowIndex    = 0;
	sf::Sprite  tile_sprite;
};

class Level
{
public:
	Level(sf::RenderWindow& window);
	~Level();

	void initTiles();

	void drawLevel(sf::RenderWindow& window);

private:
	static const int    MAX_SIZE  = 10;
	static const int    MIN_SIZE  = 3;
	static const int    TILE_SIZE = 50;
	int    GRID_SIZE;

	Tile GRID[10][10];

	std::vector<Tile> obstacles;
	
	sf::Texture empty;
	sf::Texture	obstacle;
	sf::Texture exit;
};

