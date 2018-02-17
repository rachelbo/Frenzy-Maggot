#pragma once
#include "Screen.h"


class EndLevel : public Screen
{
public:
	EndLevel(float x, float y);
	~EndLevel();
	std::string runScreen(sf::RenderWindow & window, std::vector<std::shared_ptr<Player>>& PlayerVector);
	void draw(sf::RenderWindow& window);
	void setButtonsPosition(sf::RenderWindow & window);
	std::string handleMouseReleased(float x, float y);
	void mouseMoved(float x, float y, sf::RenderWindow& window);
};