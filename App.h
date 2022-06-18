#pragma once

#include "PCH.h"
#include "Agent.h"
#include "Level.h"
#include "Algorithm.h"


class App
{
public:
	App(sf::RenderWindow& window);
	void Init();
	void Run(sf::RenderWindow& window);
	int  Close();

private:
	sf::Keyboard            keyboard;
	Agent                   agent;
	std::unique_ptr<Level>  level;
	Algorithm               algorithm;

	INPUT        keys = INPUT::NONE;
	APP_STATE    state = APP_STATE::ONINIT;

	~App();
	void MoveAgent();
	void Update();
	void Draw(sf::RenderWindow& widnow);
	void TakeInput(INPUT& keys);
	INPUT mapKeys(sf::Keyboard &keyboard);
};

