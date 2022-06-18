#include "App.h"

App::App(sf::RenderWindow& window)
{
	keys = INPUT::NONE;
	level = std::make_unique<Level>(window);
}

App::~App()
{
}

void App::Init()
{
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

		window.clear();

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

void App::TakeInput(INPUT& keys)
{
	switch (keys)
	{
	case INPUT::INC_SIZE:
		break;

	case INPUT::DEC_SIZE:
		break;

	case INPUT::RESET:
		break;

	case INPUT::QUIT:
		break;

	default:
		break;
	}
}

void App::Draw(sf::RenderWindow& window)
{
	level->drawLevel(window);
}
