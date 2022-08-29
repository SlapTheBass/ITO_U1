#pragma once

#include "PCH.h"

class Input
{
public:
	/*default constructor*/
	Input();
	/*default destructor*/
	~Input();

	/*check if key is pressed
	  and returns enumerator 
	  code for specific event
	*/
	E_keys pressedKey();

private:
	E_keys _keyHandler;
	sf::Keyboard _keyboard;
};