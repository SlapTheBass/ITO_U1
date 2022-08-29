#include "Input.h"

Input::Input()
{
	_keyHandler = eNONE;
}

Input::~Input()
{

}

E_keys Input::pressedKey() //map pressed keys int enumerator codes
{

	if (_keyboard.isKeyPressed(sf::Keyboard::LShift) || _keyboard.isKeyPressed(sf::Keyboard::RShift))
	{
		_keyHandler = eINC_SIZE;
	}
	else if (_keyboard.isKeyPressed(sf::Keyboard::LControl) || _keyboard.isKeyPressed(sf::Keyboard::RControl))
	{
		_keyHandler = eDEC_SIZE;
	}
	else if (_keyboard.isKeyPressed(sf::Keyboard::Space))
	{
		_keyHandler = eSPACE;
	}
	else if (_keyboard.isKeyPressed(sf::Keyboard::R))
	{
		_keyHandler = eRESET;
	}
	else if (_keyboard.isKeyPressed(sf::Keyboard::Escape))
	{
		_keyHandler = eQUIT;
	}
	else
	{
		_keyHandler = eNONE;
	}

	return _keyHandler;
}