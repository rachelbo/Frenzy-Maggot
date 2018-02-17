#pragma once
//----------------------------------includes-----------------------------------
#include "Screen.h"

//----------------------------------class--------------------------------------
class Help: public Screen
{
public:
	Help(float x, float y);
	~Help();
	std::string runScreen(sf::RenderWindow & window, std::vector<std::shared_ptr<Player>>& PlayerVector);
	void draw(sf::RenderWindow& window) {}
	void setButtonsPosition(sf::RenderWindow & window) {}
	std::string handleMouseReleased(float x, float y) { return ""; }
};

