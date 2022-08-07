#pragma once

#include <PCH.h>
#include "Utils.h"

class Object
{
public:
	sf::Vector2i GetPosition();
	void SetPosition(int x, int y);

	void Draw(sf::RenderWindow* window);

	E_objectType GetType() const;

	Object();
	~Object();

	sf::Sprite _sprite;
	sf::Vector2f _position;

	E_objectType _type;
};