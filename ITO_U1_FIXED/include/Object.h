#pragma once

#include <PCH.h>
#include "Utils.h"

/*base  class for  exit and  obstacle
* it  allows to  easier  generating objects
* using polimorphism
*/
class Object 
{
public:
	void Draw(sf::RenderWindow* window);

	E_objectType GetType() const;

	Object();
	~Object();

	sf::Sprite _sprite;
	sf::Vector2f _position;

	E_objectType _type;
};