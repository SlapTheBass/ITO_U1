#pragma once

#include <PCH.h>
#include <Utils.h>
#include <Object.h>

class Exit : public Object
{
public:
	Exit(sf::Vector2f position);
	~Exit();


private:
	sf::Texture _tex;
};

