#pragma once
//----------------------------------includes-----------------------------------
#include "Singleton.h"
#include "Menu.h"

//----------------------------------class--------------------------------------
class Controller
{
public:
	Controller();
	void buildScreens(float x, float y);

private:
	std::unordered_map<std::string, sf::Music> m_music;				//music
	std::map<std::string, std::shared_ptr<Screen>> m_screenMap;		//screens map
	std::vector<std::shared_ptr<Player>> m_playerVector;			//players vector
};

