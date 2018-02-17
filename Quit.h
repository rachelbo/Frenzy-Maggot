#pragma once
//----------------------------------includes-----------------------------------
#include "Screen.h"

//----------------------------------class--------------------------------------
class Quit : public Screen
{
public:
	Quit(float x, float y);
	~Quit();
	std::string runScreen(sf::RenderWindow & window, std::vector<std::shared_ptr<Player>>& PlayerVector) { return ""; }
	void draw(sf::RenderWindow& window) {}
	void setButtonsPosition(sf::RenderWindow & window) {}
	std::string handleMouseReleased(float x, float y) { return ""; }
};

