#pragma once
//----------------------------------includes-----------------------------------
#include "Singleton.h"
#include "Buttons.h"
#include "Player.h"

//----------------------------------class--------------------------------------
class Screen
{
public:
	Screen(float x, float y);
	~Screen();
	virtual std::string runScreen(sf::RenderWindow & window, std::vector<std::shared_ptr<Player>>& PlayerVector) = 0;
	virtual void draw(sf::RenderWindow& window) = 0;
	virtual void setButtonsPosition(sf::RenderWindow & window) = 0;
	virtual std::string handleMouseReleased(float x, float y) = 0;

protected:
	sf::Music m_music;					//music
	float m_scaleX_background;			//x scale background
	float m_scaleY_background;			//y scale background
	sf::Sprite m_backgroundSprite;		//background sprite
	std::map<std::string, std::shared_ptr<Buttons>> m_myButtonMap;		//buttons map
	std::vector<std::shared_ptr<Player>> m_playerVec;					//players vector
};

