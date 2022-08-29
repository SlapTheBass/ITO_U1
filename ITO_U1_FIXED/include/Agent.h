#pragma once

#include "PCH.h" 

class Agent
{
public:
	/* Parametrized constructor
	   creates Agent on given position
	*/
	Agent(sf::Vector2f position);

	/* Default  destructor */
	~Agent();

	/* Agent drawing  method */
	void Draw(sf::RenderWindow* window);

	/* Sprite position setting and getting methods */
	void SetPosition(sf::Vector2f position);
	sf::Vector2f GetPosition();

private:
	sf::Sprite  _sprite;
	sf::Texture _texture;

	int x, y;
};