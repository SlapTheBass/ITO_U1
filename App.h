#pragma once

#include "PCH.h"
#include "Agent.h"
#include "Level.h"
#include "Algorithm.h"


class App
{
public:
	App();
	void Init();
	void Run();
	int  Close();

private:
	sf::Window mainWindow;
	sf::Keyboard keyboard;
	Agent agent;
	Level level;
	Algorithm algorithm;
	INPUT keys = INPUT::NONE;

	~App();
	void TakeInput(INPUT &keys);
	INPUT mapKeys(sf::Keyboard &keyboard);
};

