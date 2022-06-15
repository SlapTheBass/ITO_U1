#pragma once

#include "PCH.h" 
#include "TextureManager.h"

class Agent
{
public:
	Agent();
	~Agent();

	void move();

	sf::Sprite getSprite();

private:
	sf::Sprite  p_sprite;
	sf::Texture p_texture;
};

