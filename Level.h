#pragma once

#include "PCH.h"

struct Tile
{
	Tile*       parent      = nullptr;
	TILE_TYPE   type        = TILE_TYPE::EMPTY;
	float       reward      = 0.0f;
	int         columnIndex = 0;
	int         rowIndex    = 0;
	sf::Sprite  tile_sprite;
};

class Level
{
public:
	Level();
	~Level();

	void initTiles();

	void incSize(sf::Clock* timer);
	void decSize(sf::Clock* timer);
	void keepSize(sf::Clock* timer);

	void generateObstacles();

	void drawLevel(sf::RenderWindow& window);

	void generateExits();
	void reset(sf::RenderWindow& window);
	void checkExits();
	void checkObstacles();

	int getLevelSize();
	int getObstaclesNumber();

	Tile* GetTile(sf::Vector2i position, sf::RenderWindow& window);
	Tile* getTile(int x, int y);

	void setAgentPos(sf::Vector2i pos);

private:
	static const int    MAX_SIZE  = 10;
	static const int    MIN_SIZE  = 3;
	static const int    TILE_SIZE = 50;

	int NORTH_x, NORTH_y, SOUTH_x, SOUTH_y, EAST_x, EAST_y, WEST_x, WEST_y;

	int agent_x, agent_y;

	int    GRID_SIZE;

	Tile GRID[10][10];

	std::vector<Tile> obstacles;
	
	sf::Texture empty;
	sf::Texture	obstacle;
	sf::Texture exit;

};

