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

		level.setStartTile(sf::Vector2i(col, row));
		level.setAgentPos(sf::Vector2i(col, row));
		x = col;
		y = row;
		p_sprite.setPosition((100.f * col) + 50, (100.f * row) + 40);
	}
}

sf::Sprite Agent::getSprite()
{
	return p_sprite;
}

void Agent::move(Level& level)
{
	p_sprite.setPosition((100.f * level.getAgent().x) + 50, (100.f * level.getAgent().y) + 40);

	ACTION vec = level.getSequence();


	if (vec == ACTION::EAST)
	{
		x = x - 1;
		y = y;
		level.setAgentPos(sf::Vector2i(x, y));
		p_sprite.setPosition((100.f * x) + 50, (100.f * y) + 40);
	}
	else if (vec == ACTION::WEST)
	{
		x = x + 1;
		y = y;
		level.setAgentPos(sf::Vector2i(x, y));
		p_sprite.setPosition((100.f * x) + 50, (100.f * y) + 40);
	}
	else if (vec == ACTION::NORTH)
	{
		x = x;
		y = y + 1;
		level.setAgentPos(sf::Vector2i(x, y));
		p_sprite.setPosition((100.f * x) + 50, (100.f * y) + 40);
	}
	else
	{
		x = x;
		y = y - 1;
		level.setAgentPos(sf::Vector2i(x, y));
		p_sprite.setPosition((100.f * x) + 50, (100.f * y) + 40);
	}

}