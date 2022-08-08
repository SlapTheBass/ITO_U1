#pragma once

#include "PCH.h"
#include "Input.h"
#include "Exit.h"
#include "Obstacle.h"
#include "Agent.h"

struct Tile
{
	E_tileType   type = eEMPTY;
	E_tileStatus status = eINACTIVE;
	float       reward = 0.0f;
	int         columnIndex = 0;
	int         rowIndex = 0;
	sf::Sprite  tile_sprite;
};

class Level
{
public:
	/* Default constructor */
	Level();

	/* Default destructor */
	~Level();

	/* Drawing level method
	  @Param takes pointer to sf::Window
	  @Returns void */
	void drawLevel(sf::RenderWindow* window);

	/* Level Update method
	   @Params - takes input, and timer for 
	   processing level parameters 
	*/
	void Update(Input& input, sf::Clock* timer);

	int getLevelSize();
	int getObstaclesNumber();

	Tile* GetTile(sf::Vector2i position);
	Tile* GetTile(int x, int y);

	void setAgentPos(sf::Vector2i pos);


	sf::Vector2i getAgent();

	

	E_action getSequence();

private:
	static const int    MAX_SIZE = 10;
	static const int    MIN_SIZE = 3;
	static const int    TILE_SIZE = 50;

	int NORTH_x, NORTH_y, SOUTH_x, SOUTH_y, EAST_x, EAST_y, WEST_x, WEST_y;

	int agent_x, agent_y, start_x, start_y;

	int    GRID_SIZE;
	int    iterations;

	Tile GRID[10][10];

	std::vector<std::unique_ptr<Object>> _objects;
	Agent* _agent;
	std::vector<std::tuple<int, sf::Vector2i, float>> grids;
	E_action path;

	sf::Texture empty;
	sf::Texture	obstacle;
	sf::Texture exit;
	sf::Clock timer;
	float gain = 0;
	bool run = false;


	/* Input depednet methods 
	   @Param timer allows to
	   detect single press of 
	   keyboard buttons  
	 */
	void incSize(sf::Clock* timer);
	void decSize(sf::Clock* timer);
	void resetAgent(sf::Clock* timer);

	void reset();
	void ResetColor();
	

	void initTiles();

	void generateObstacles();

	void setStartTile(sf::Vector2i pos);

	void generateExits();
	void generatePlayerTile();

	void SpawnObjects();
	
	void checkExits();
	void checkObstacles();
};