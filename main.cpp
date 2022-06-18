#include "App.h"

int main()
{
	sf::RenderWindow mainWindow(sf::VideoMode::getDesktopMode(), "Reinforcement learning project", sf::Style::Resize);
	mainWindow.setSize(sf::Vector2u(1024, 720));
	mainWindow.setPosition(sf::Vector2i(sf::VideoMode::getDesktopMode().width/2 - 512, sf::VideoMode::getDesktopMode().height/2 - 480));


	App* Application = new App(mainWindow);

	Application->Init();
	Application->Run(mainWindow);
}