#pragma once

#include "PCH.h"
#include "Agent.h"
#include "Level.h"
#include "Input.h"
#include "UserInterface.h"

class App
{
public:
	/*default constructor*/
	App();

	/*main loop*/
	void Run();

private:
	sf::RenderWindow* _window;
	sf::Clock         _timer;
	sf::Sprite	      _cursour;
	sf::Texture       _cursourTexture;

	Input       _input;
	E_appState  _state = eONINIT;

	std::unique_ptr<UserInterface> _UI;
	std::unique_ptr<Level> _level;
	std::unique_ptr<Agent> _agent;

	/*default destructor*/
	~App();

	/*this method initializes all application members*/
	void Init();

	/*update members*/
	void Update();

	/*draw members and visualize main window*/
	void Draw();
};