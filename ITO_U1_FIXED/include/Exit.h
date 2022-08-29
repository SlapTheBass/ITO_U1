#pragma once

#include <PCH.h>
#include <Utils.h>
#include <Object.h>

class Exit : public Object
{
public:
	/* parametrized constructor
	   it creates exit in given position
	*/
	Exit(sf::Vector2f position);
	~Exit();


private:
	sf::Texture _tex;
};

