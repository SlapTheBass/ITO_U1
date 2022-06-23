#include "UserInterface.h"

UserInterface::UserInterface(Level& level, Agent& agent, sf::Vector2i position, sf::RenderWindow& window)
{
	Update(level, agent, position, window);

	font.loadFromFile("UTILS/font.ttf");
	
	keys.setFont(font);
	keys.setString("[ESC] - Close application\n\n\n[Left Shift] - increase level size\n\n\n[Left Ctrl] - decrease level size\n\n\n[R] - reset");
	keys.setPosition(sf::Vector2f(1200, 50));
	keys.setFillColor(sf::Color::White);
	keys.setCharacterSize(22);

	size.setFont(font);
	size.setString("Level size:  " + std::to_string(level_size) + " x " + std::to_string(level_size));
	size.setPosition(sf::Vector2f(1200, 350));
	size.setFillColor(sf::Color::Yellow);
	size.setCharacterSize(22);

	obstacles.setFont(font);
	obstacles.setString("Number of obstacles: " + std::to_string(obstacles_number));
	obstacles.setPosition(sf::Vector2f(1200, 400));
	obstacles.setFillColor(sf::Color::Yellow);
	obstacles.setCharacterSize(22);

	info.setFont(font);
	info.setString("================= TILE INFO ================\n\ncolumn index: " + std::to_string(column_index) + "\trow index: " + std::to_string(row_index)
					+ "\n\naverage reward: " + std::to_string(average_reward) +  "\n\ndiscount: " + std::to_string(discount));
	info.setPosition(sf::Vector2f(1200, 800));
	info.setFillColor(sf::Color::Green);
	info.setCharacterSize(22);

	type.setFont(font);
	type.setString("TILE TYPE:  ");
	type.setPosition(sf::Vector2f(1200, 1000));
	type.setFillColor(sf::Color::Magenta);
	type.setCharacterSize(22);
}

UserInterface::~UserInterface()
{
}

void UserInterface::Draw(sf::RenderWindow& window)
{
	window.draw(keys);
	window.draw(size);
	window.draw(obstacles);
	window.draw(info);
	window.draw(type);
}

void UserInterface::Update(Level& level, Agent& agent, sf::Vector2i position, sf::RenderWindow& window)
{
	level_size = level.getLevelSize();
	size.setString("Level size:  " + std::to_string(level_size) + " x " + std::to_string(level_size));

	obstacles_number = level.getObstaclesNumber();
	obstacles.setString("Number of obstacles: " + std::to_string(obstacles_number));

	column_index = level.GetTile(position, window)->columnIndex;
	row_index = level.GetTile(position, window)->rowIndex;
	std::cout << level.GetTile(position, window)->reward << "\n\n";
	average_reward = level.GetTile(position, window)->reward;
	discount = 0.9;

	if (column_index >= level.getLevelSize())
	{
		info.setString("================= TILE INFO ================\n\ncolumn index: \t\trow index:\n\naverage reward: " + std::to_string(average_reward) + 
			"\n\ndiscount: " + std::to_string(discount));
	}
	else if (row_index >= level.getLevelSize())
	{
		info.setString("================= TILE INFO ================\n\ncolumn index: \t\trow index:\n\naverage reward: " + std::to_string(average_reward) +
			"\n\ndiscount: " + std::to_string(discount));
	}
	else
	{
		info.setString("================= TILE INFO ================\n\ncolumn index: " + std::to_string(column_index) + "\trow index: " + std::to_string(row_index)
			+ "\n\naverage reward: " + std::to_string(average_reward) + "\n\ndiscount: " + std::to_string(discount));
	}
	
	switch (level.GetTile(position, window)->type)
	{
	case TILE_TYPE::EMPTY:
		TYPE = "EMPTY";
		break;

	case TILE_TYPE::AGENT:
		TYPE = "AGENT";
		break;

	case TILE_TYPE::EXIT:
		TYPE = "EXIT";
		break;

	case TILE_TYPE::OBSTACLE:
		TYPE = "OBSTACLE";
		break;

	deafault:
		TYPE = "  ";
		break;
	}

	type.setString("TILE TYPE:  " + TYPE);
}