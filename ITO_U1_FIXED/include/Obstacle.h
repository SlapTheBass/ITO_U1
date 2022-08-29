#pragma once

#include "Object.h"
#include "PCH.h"
#include "Utils.h"

class Obstacle : public Object
{
public:
	/*parametrized constructor
	  it creates obstacle in given position
	*/
	Obstacle(sf::Vector2f postion);
	/*default destructor*/
	~Obstacle();

private:
	sf::Texture _tex;
};