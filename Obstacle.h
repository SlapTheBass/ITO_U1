#pragma once

#include "PCH.h"

class Obstacle
{
public:
	Obstacle();
	~Obstacle();

	void setXpos(int x);
	void setYpos(int y);

	int getXpos(void);
	int getYpos(void);

	sf::Sprite getSprite(void);

private:
	Tile tile;

	sf::Sprite  o_sprite;
	sf::Texture o_texture;
};

