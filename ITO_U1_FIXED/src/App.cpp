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
	_window = new sf::RenderWindow(sf::VideoMode(1024, 600), "RL Project"); 
	_window->setKeyRepeatEnabled(true);

	_level = new Level();
	_UI = new UserInterface();
}

void App::Update()
{
	_level->Update(_input, &_timer);
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

		_window->clear();

		Update();

		Draw();
	}
}

void App::Draw()
{
	_UI->Draw(_window);
	_level->drawLevel(_window);
	_window->display();
}

