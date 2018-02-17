#pragma once
//----------------------------------includes-----------------------------------
#include "Singleton.h"

//----------------------------------class--------------------------------------
class Buttons
{
public:
	Buttons();
	sf::Sprite& getSprite() { return m_sprite; }
	virtual std::string getMyScreen() { return m_myScreen; }
	void setOpacity(unsigned opacity) { m_sprite.setColor(sf::Color(255, 255, 255, opacity)); }
	~Buttons();
protected:
	std::string m_myScreen;		//screen string	
	sf::Sprite m_sprite;		//sprite memebr
};
//----------------------------------class--------------------------------------
class PlayButton : public Buttons
{
public:
	PlayButton() { m_sprite.setTexture(Singleton::instance().getTexture("play_button")); m_myScreen = "class ChoosePlayer"; } //m_myScreen= "choosePlayerWin" צריך להיות 
};
//----------------------------------class--------------------------------------
class ExitButton : public Buttons
{
public:
	ExitButton() { m_sprite.setTexture(Singleton::instance().getTexture("exit_button")); m_myScreen = "class Quit";	}
};
//----------------------------------class--------------------------------------
class HelpButton : public Buttons
{
public:
	HelpButton() { m_sprite.setTexture(Singleton::instance().getTexture("help_button")); m_myScreen = "class Help"; }
};
//----------------------------------class--------------------------------------
class PauseButton : public Buttons
{
public:
	PauseButton() { m_sprite.setTexture(Singleton::instance().getTexture("help_button")); m_myScreen = "class Help"; };
};
//----------------------------------class--------------------------------------
class MenuButton : public Buttons
{
public:
	MenuButton() { m_sprite.setTexture(Singleton::instance().getTexture("return_button")); m_myScreen = "class Menu";}
};
//----------------------------------class--------------------------------------
class NewGameButton : public Buttons
{
public:
	NewGameButton() { m_sprite.setTexture(Singleton::instance().getTexture("play_button")); m_myScreen = "class Play"; };
};