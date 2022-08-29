#pragma once

#include "PCH.h"
#include "Level.h"
#include "Agent.h"
#include "Algorithm.h"

class UserInterface
{
public:
	/*default constructor*/
	UserInterface();
	/*default destructor*/
	~UserInterface();

	/*update method
	  it takes values from level
	  and allows to display them 
	  as members of user interface
	*/
	void Update(Level* level);
	/*ui draw method*/
	void Draw(sf::RenderWindow* window);

private:
	int level_size = 0;
	int agent_moves = 0;
	int obstacles_number = 0;
	int column_index = 0;
	int row_index = 0;
	float average_reward = 0;
	float discount = 0;
	std::string TYPE;

	sf::Text size, moves, obstacles, keys, info, type;
	sf::Font font;
};