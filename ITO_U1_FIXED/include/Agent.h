#pragma once

#include "PCH.h" 
#include "Level.h"

class Agent
{
public:
	Agent();
	~Agent();

	void move(Level& level);

	void Draw(sf::RenderWindow& window);

	void Spawn(Level& level, sf::Clock* timer);

	sf::Sprite getSprite();

private:
	sf::Sprite  p_sprite;
	sf::Texture p_texture;

	int x, y;
};