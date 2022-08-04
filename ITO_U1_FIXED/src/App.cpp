#include "App.h"

App::App()
{
	Init();
}

App::~App()
{

}

void App::Init()
{
	_window = new sf::RenderWindow(sf::VideoMode(1024, 576), "RL Project"); //
	_window->setKeyRepeatEnabled(true);
}

void App::Update()
{

}

void App::Run()
{
	while (_window->isOpen())
	{
		sf::Event event;

		while (_window->pollEvent(event))  //polling event allows to move our window on the screen
		{
			if (event.type == sf::Event::Closed || _input.pressedKey() == eQUIT)
			{
				_state = eCLOSE;
				_window->close();
				break;
			}
		}

		Update();

		Draw();
		
	}
}

void App::Draw()
{
	_window->clear();

	_window->display();
}

