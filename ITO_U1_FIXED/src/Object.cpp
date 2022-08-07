#include "Object.h"

Object::Object()
{

}

Object::~Object()
{

}

E_objectType Object::GetType() const
{
	return _type;
}

void Object::Draw(sf::RenderWindow* window)
{
	window->draw(_sprite);
}
