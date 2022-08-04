#pragma once

#include "PCH.h"

class Input
{
public:
	Input();
	~Input();

	E_keys pressedKey();

private:
	E_keys _keyHandler;
	sf::Keyboard _keyboard;
};