#include "Agent.h"

Agent::Agent()
{
	p_texture.loadFromFile("UTILS/spr_agent.png");
	p_sprite.setTexture(p_texture);
	p_sprite.setScale(2.0f, 2.0f);
}

Agent::~Agent()
{
}

void Agent::Draw(sf::RenderWindow& window)
{
	window.draw(p_sprite);
}

void Agent::Spawn(Level& level, sf::Clock* timer)
{
	if (timer->getElapsedTime().asMilliseconds() >= 50)
	{
		int col = rand() % (level.getLevelSize() - 1);
		int row = rand() % (level.getLevelSize() - 1);

		while ((level.getTile(col, row)->type != TILE_TYPE::EMPTY) || col == level.getLevelSize() - 1 || row == level.getLevelSize() - 1 ||
			col == 0 || row == 0)
		{
			col = rand() % (level.getLevelSize() - 1);
			row = rand() % (level.getLevelSize() - 1);
		}

		level.setAgentPos(sf::Vector2i(col, row));
		p_sprite.setPosition((100.f * col) + 50, (100.f * row) + 40);
	}
}

sf::Sprite Agent::getSprite()
{
	return p_sprite;
}