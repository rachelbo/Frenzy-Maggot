#pragma once
//----------------------------------includes-----------------------------------
#include "Screen.h"
#include "Player.h"

//----------------------------------class--------------------------------------
class ChoosePlayer : public Screen
{
public:
	ChoosePlayer(float x, float y, std::vector<std::shared_ptr<Player>>& PlayerVector);
	std::string runScreen(sf::RenderWindow & window, std::vector<std::shared_ptr<Player>>& PlayerVector);
	void draw(sf::RenderWindow& window);
	void setButtonsPosition(sf::RenderWindow & window);
	std::string handleMouseReleased(float x, float y);
	void mouseMoved(float x, float y, sf::RenderWindow & window);

private:
	std::vector<std::shared_ptr<Player>> m_playerVec;		//vector of players
};

