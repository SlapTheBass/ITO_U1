#include "App.h"

App::App(sf::RenderWindow& window)
{
	aim_tex.loadFromFile("UTILS/aim.png");
	aim.setTexture(aim_tex);

	keys = INPUT::NONE;

	level = std::make_unique<Level>();

	agent = std::make_unique<Agent>();
	agent->Spawn(*level, &timer);

	timer.restart();

	UI = std::make_unique<UserInterface>(*level, *agent, sf::Vector2i(0,0), window);

}

App::~App()
{
}

void App::Init()
{
}

void App::Update(sf::RenderWindow& window)
{
	sf::Vector2i mousePos = sf::Mouse::getPosition();
	aim.setPosition((float)mousePos.x, (float)mousePos.y);

	UI->Update(*level, *agent, mousePos, window);
}

void App::Run(sf::RenderWindow& window)
{
	while (window.isOpen())
	{
		if (mapKeys(keyboard) == INPUT::QUIT)
		{
			state = APP_STATE::CLOSE;
			window.close();
			break;
		}

		if (mapKeys(keyboard) == INPUT::INC_SIZE)
		{
			level->reset(window);
			level->incSize(&timer);
			agent->Spawn(*level, &timer);
			timer.restart();
			algorithm.calculaRewards(*level);
		}

		if (mapKeys(keyboard) == INPUT::DEC_SIZE)
		{
			level->reset(window);
			level->decSize(&timer);
			agent->Spawn(*level, &timer);
			timer.restart();
			algorithm.calculaRewards(*level);
		}

		if (mapKeys(keyboard) == INPUT::RESET)
		{
			level->reset(window);
			level->keepSize(&timer);
			agent->Spawn(*level, &timer);
			timer.restart();
			algorithm.calculaRewards(*level);
		}

		window.clear();

		Update(window);

		Draw(window);

		window.display();
	}
}

INPUT App::mapKeys(sf::Keyboard& keyboard)
{
	if (keyboard.isKeyPressed(keyboard.LShift))
	{
		keys = INPUT::INC_SIZE;
	}
	else if (keyboard.isKeyPressed(keyboard.LControl))
	{
		keys = INPUT::DEC_SIZE;
	}
	else if (keyboard.isKeyPressed(keyboard.R))
	{
		keys = INPUT::RESET;
	}
	else if (keyboard.isKeyPressed(keyboard.Escape))
	{
		keys = INPUT::QUIT;
	}
	else
	{
		keys = INPUT::NONE;
	}

	return keys;
}

void App::Draw(sf::RenderWindow& window)
{
	level->drawLevel(window);
	UI->Draw(window);
	agent->Draw(window);
	window.draw(aim);
}
