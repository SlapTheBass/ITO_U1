#pragma once

#include "Agent.h"
#include "Level.h"

class Algorithm
{
public:
	/* Default constructor  and destructor */
	Algorithm();
	~Algorithm();

	/* Seeking path method - it compares rewards of tiles around agent 
	   Agent is moved to tile  with highest reward
	*/
	void seekPath(Level* level);

	/* Method calulates average rewards for all subgrids generated for specific  objects */
	void calculateRewards(Level* level);

	/* Reset parameters */
	void Reset();

	/* Check if agent can move */
	bool CanMove();

	/* Check if exit has been found*/
	bool ExitFound();

private:
	std::vector<std::tuple<int, sf::Vector2i, float>> grids;
	E_tileType tempType = eEMPTY;
	Tile* _grid[10][10];
	bool canMove = true;
	bool reset = false;
	bool exitFound = false;

	int iterations;
	float horizontal, vertical;
	float gain;
	bool eastBorder;
	bool westBorder;
	bool northBorder;
	bool southBorder;
	float discount = 0.9f;

	/* Method create subgrids for every object placed on level 
	   then it calculates separate rewards for them and places them in tuple
	*/
	void FindR(Level* level);

	/* it copies  actual grid state into local grid */
	void GridInit(Level* level);

	/*  Checks type of tile that is about to be occupied by agent 
	    it calculates consequences also
	*/
	void CheckTile(Tile* tile, Tile* agentTile);

	/* Compares horizontal tiles around agent */
	void HorizontalCheck(Tile* EAST, Tile* WEST, Tile* agentTile);
	/* Compares vertical tiles around agent*/
	void VerticalCheck(Tile* NORTH, Tile* SOUTH, Tile* agentTile);
	/* Compares tiles around agent in case when agent position meets level horizontal border */
	void HorizontalBorderCheck(Tile* tile1, Tile* tile2, Tile* tile3, Tile* agentTile);
	/* Compares tiles around agent in case  when agent position meets level vertical border */
	void VerticalBorderCheck(Tile* tile1, Tile* tile2, Tile* tile3, Tile* agentTile);

	/* Check borders */
	bool CanMoveWest(Tile* tile, int size);
	bool CanMoveEast(Tile* tile, int size);
	bool CanMoveNorth(Tile* tile, int size);
	bool CanMoveSouth(Tile* tile, int size);
};