//----------------------------------includes-----------------------------------
#include "Controller.h"
#include "Singleton.h"
#include "ChoosePlayer.h"
#include "Menu.h"
#include "Play.h"
#include "Help.h"
#include "Quit.h"

//----------------------------------c-tor--------------------------------------
Controller::Controller()
{
	auto desktopMode = sf::VideoMode::getDesktopMode();
	sf::RenderWindow window(sf::VideoMode(desktopMode.width, desktopMode.height), "Frenzy Maggot");
	window.setPosition(sf::Vector2i(0, 0));

	auto windowSize = window.getSize();
	auto scaleX = (float)windowSize.x / Singleton::instance().getTexture("menu").getSize().x;
	auto scaleY = (float)windowSize.y / Singleton::instance().getTexture("menu").getSize().y;
	buildScreens(scaleX, scaleY);

	std::string currentString = typeid(Menu).name();
	if (!m_music[typeid(Menu).name()].openFromFile("music/Choro_bavario.ogg"))
		exit(1);
	m_music[typeid(Menu).name()].setLoop(true);
	
	if (!m_music[typeid(Play).name()].openFromFile("music/one.ogg"))
		exit(1);
	m_music[typeid(Play).name()].setLoop(true);
	
	m_music[typeid(Menu).name()].play();

	while (currentString != typeid(Quit).name())
	{
		if (currentString == typeid(Play).name()) {
			m_music[typeid(Menu).name()].stop();
			m_music[typeid(Play).name()].play();
		}

		currentString = m_screenMap[currentString]->runScreen(window, m_playerVector);
		
		if (currentString == typeid(Menu).name()) {
			m_music[typeid(Play).name()].stop();
			m_music[typeid(Menu).name()].play();
		}


	}
	window.close();
} 
//-----------------------------------------------------------------------------
//this function builds a map of screens
void Controller::buildScreens(float x, float y)
{
	m_screenMap.emplace(typeid(Menu).name(), std::make_shared<Menu>(x,y));
	m_screenMap.emplace(typeid(Play).name(), std::make_shared<Play>(x,y));
	m_screenMap.emplace(typeid(Help).name(), std::make_shared<Help>(x,y));
	m_screenMap.emplace(typeid(ChoosePlayer).name(), std::make_shared<ChoosePlayer>(x,y, m_playerVector));
	m_screenMap.emplace(typeid(Quit).name(), std::make_shared<Quit>(x, y));
}