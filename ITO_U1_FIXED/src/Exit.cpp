#include "Exit.h"

Exit::Exit(sf::Vector2f position)
{
	_tex.loadFromFile("Utilities/spr_exit.png");
	_type = E_objectType::eEXIT;
	_sprite.setTexture(_tex);
	_sprite.setPosition(position);
}

Exit::~Exit()
{

}