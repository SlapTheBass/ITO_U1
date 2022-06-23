#include <time.h>
#include "App.h"

int main()
{
	srand(static_cast<int>(time(nullptr)));

	sf::RenderWindow mainWindow(sf::VideoMode::getDesktopMode(), "Reinforcement learning project", sf::Style::Resize);
	mainWindow.setSize(sf::Vector2u(1024, 576));
	mainWindow.setKeyRepeatEnabled(false);
	mainWindow.setPosition(sf::Vector2i(sf::VideoMode::getDesktopMode().width/2 - 512, sf::VideoMode::getDesktopMode().height/2 - 480));
	mainWindow.setMouseCursorVisible(false);

	App* Application = new App(mainWindow);

	Application->Init();
	Application->Run(mainWindow);
}