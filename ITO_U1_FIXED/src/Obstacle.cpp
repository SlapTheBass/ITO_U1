#include "Obstacle.h"

Obstacle::Obstacle(sf::Vector2f position)
{
	_tex.loadFromFile("Utilities/spr_bush.png");
	_type = E_objectType::eOBSTACLE;
	_sprite.setTexture(_tex);
	_sprite.setPosition(position);
}

Obstacle::~Obstacle()
{

}