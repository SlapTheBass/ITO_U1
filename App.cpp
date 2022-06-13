#include "App.h"

App::App()
{
	keys = INPUT::NONE;
}

App::~App()
{
}

void App::Init()
{
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
