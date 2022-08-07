#pragma once

#include "PCH.h"
#include "Level.h"
#include "Agent.h"

class UserInterface
{
public:
	UserInterface();
	~UserInterface();

	void Update(Level* level);
	void Draw(sf::RenderWindow* window);

private:
	int level_size = 0;
	int player_moves = 0;
	int obstacles_number = 0;
	int column_index = 0;
	int row_index = 0;
	float average_reward = 0;
	float discount = 0;
	std::string TYPE;

	sf::Text size, moves, obstacles, keys, info, type;
	sf::Font font;
};