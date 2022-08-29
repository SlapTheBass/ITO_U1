#include "App.h"

App::App()
{
	Init();  //initialize app on its' creation
}

App::~App()
{

}

void App::Init()
{
	_window = new sf::RenderWindow(sf::VideoMode(1024, 600), "RL Project");  //create main window
	_window->setKeyRepeatEnabled(true);

	_level = new Level(); //create level
	_UI = new UserInterface(); //create ui
	_algorithm = new Algorithm(); //create algorithm
}

void App::Update()
{
	_level->Update(_input, &_timer); 

	if (_input.pressedKey() == eSPACE) //if space is pressed algorithm calculates new position of agent
	{
		if (_timer.getElapsedTime().asMilliseconds() >= 50)
		{
			_level->ClearAgent();
			_algorithm->seekPath(_level);
			_level->SpawnAgent();
		}
		_timer.restart();
	}
	_UI->Update(_level);
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

