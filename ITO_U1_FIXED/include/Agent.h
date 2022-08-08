#pragma once

#include "PCH.h" 

class Agent
{
public:
	Agent(sf::Vector2f position);
	~Agent();

	void move();

	void Draw(sf::RenderWindow* window);

	void SetPosition(sf::Vector2f position);
	sf::Vector2f GetPosition();

private:
	sf::Sprite  _sprite;
	sf::Texture _texture;

	int x, y;
};