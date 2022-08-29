#include "UserInterface.h"

UserInterface::UserInterface()
{
	font.loadFromFile("Utilities/font.ttf");

	keys.setFont(font);
	keys.setString("[ESC] - Close application\n\n\n[Left Shift] - increase level size\n\n\n[Left Ctrl] - decrease level size\n\n\n[R] - reset\n\n\nHold [SPACE] - Agent seeks for exit");
	keys.setPosition(sf::Vector2f(750, 50));
	keys.setFillColor(sf::Color::White);
	keys.setCharacterSize(10);

	size.setFont(font);
	size.setString("Level size:  " + std::to_string(level_size) + " x " + std::to_string(level_size));
	size.setPosition(sf::Vector2f(750, 240));
	size.setFillColor(sf::Color::Yellow);
	size.setCharacterSize(10);

	obstacles.setFont(font);
	obstacles.setString("Number of obstacles: " + std::to_string(obstacles_number));
	obstacles.setPosition(sf::Vector2f(750, 255));
	obstacles.setFillColor(sf::Color::Yellow);
	obstacles.setCharacterSize(10);

	moves.setFont(font);
	moves.setString("AGENT - steps left: " + std::to_string(agent_moves));
	moves.setPosition(sf::Vector2f(750, 275));
	moves.setFillColor(sf::Color::Cyan);
	moves.setCharacterSize(10);

	info.setFont(font);
	info.setString("================= TILE INFO ================\n\ncolumn index: " + std::to_string(column_index) + "\trow index: " + std::to_string(row_index)
		+ "\n\naverage reward: " + std::to_string(average_reward) + "\n\ndiscount: " + std::to_string(discount));
	info.setPosition(sf::Vector2f(750, 350));
	info.setFillColor(sf::Color::Green);
	info.setCharacterSize(10);

	type.setFont(font);
	type.setString("TILE TYPE:  ");
	type.setPosition(sf::Vector2f(750, 500));
	type.setFillColor(sf::Color::Magenta);
	type.setCharacterSize(10);
}

UserInterface::~UserInterface()
{

}

void UserInterface::Draw(sf::RenderWindow* window)
{
	/*draw every single text object on the screen*/
	window->draw(keys);
	window->draw(size);
	window->draw(obstacles);
	window->draw(info);
	window->draw(type);
	window->draw(moves);
}

void UserInterface::Update(Level* level)
{
	sf::Vector2i position = sf::Mouse::getPosition(); //save mouse position into variable

	level_size = level->getLevelSize();
	size.setString("Level size:  " + std::to_string(level_size) + " x " + std::to_string(level_size));

	obstacles_number = level->getObstaclesNumber();
	obstacles.setString("Number of obstacles: " + std::to_string(obstacles_number));

	agent_moves = level->GetSteps();
	moves.setString("AGENT - steps left: " + std::to_string(agent_moves));

	/*call method to get tile information
	  additional effect is changing color of tile to darker
	*/
	column_index = level->GetTile(position)->columnIndex;
	row_index = level->GetTile(position)->rowIndex;
	average_reward = level->GetTile(position)->reward;
	discount = 0.9;


	/*display tile information*/
	if (column_index >= level->getLevelSize())
	{
		info.setString("================= TILE INFO ================\n\ncolumn index: \t\trow index:\n\naverage reward: " + std::to_string(average_reward) +
			"\n\ndiscount: " + std::to_string(discount));
	}
	else if (row_index >= level->getLevelSize())
	{
		info.setString("================= TILE INFO ================\n\ncolumn index: \t\trow index:\n\naverage reward: " + std::to_string(average_reward) +
			"\n\ndiscount: " + std::to_string(discount));
	}
	else
	{
		info.setString("================= TILE INFO ================\n\ncolumn index: " + std::to_string(column_index) + "\trow index: " + std::to_string(row_index)
			+ "\n\naverage reward: " + std::to_string(average_reward) + "\n\ndiscount: " + std::to_string(discount));
	}

	switch (level->GetTile(position)->type)
	{
	case eEMPTY:
		TYPE = "EMPTY";
		break;

	case eAGENT:
		TYPE = "AGENT";
		break;

	case eEXIT:
		TYPE = "EXIT";
		break;

	case eOBSTACLE:
		TYPE = "OBSTACLE";
		break;

	case eVOID:
		TYPE = "  ";
		break;

	deafault:
		TYPE = "  ";
		break;
	}

	type.setString("TILE TYPE:  " + TYPE);
}