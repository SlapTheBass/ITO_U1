#pragma once

#include "PCH.h"
#include "Agent.h"
#include "Level.h"
#include "Algorithm.h"
#include "UserInterface.h"


class App
{
public:
	App(sf::RenderWindow& window);
	void Init();
	void Run(sf::RenderWindow& window);
	int  Close();

private:
	sf::Keyboard keyboard;
	sf::Clock    timer;
	sf::Sprite	 aim;
	sf::Texture  aim_tex;
	Algorithm    algorithm;

	INPUT        keys = INPUT::NONE;
	APP_STATE    state = APP_STATE::ONINIT;

	std::unique_ptr<UserInterface> UI;
	std::unique_ptr<Level> level;
	std::unique_ptr<Agent> agent;

	~App();
	void MoveAgent(ACTION action);
	void Update(sf::RenderWindow& window);
	void Draw(sf::RenderWindow& widnow);
	INPUT mapKeys(sf::Keyboard &keyboard);
};

