#pragma once

#include "Object.h"
#include "PCH.h"
#include "Utils.h"

class Obstacle : public Object
{
public:
	Obstacle(sf::Vector2f postion);
	~Obstacle();

private:
	sf::Texture _tex;
};