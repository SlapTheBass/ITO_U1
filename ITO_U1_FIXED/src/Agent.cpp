#include "Agent.h"

Agent::Agent(sf::Vector2f position)
{
	_texture.loadFromFile("Utilities/spr_agent.png"); //set texture of agent
	_sprite.setTexture(_texture);
	_sprite.setPosition(position);
}

Agent::~Agent()
{

}


void Agent::Draw(sf::RenderWindow* window)
{
	window->draw(_sprite);
}

void Agent::SetPosition(sf::Vector2f position)
{
	_sprite.setPosition(sf::Vector2f(position.x * 50 + 120, position.y * 50 + 50)); //set agent sprite position
}

sf::Vector2f Agent::GetPosition()
{
	return _sprite.getPosition(); //get agent  sprite position
}