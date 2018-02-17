//----------------------------------includes-----------------------------------
#include "Menu.h"

//----------------------------------c-tor--------------------------------------
Menu::Menu(float x, float y) : Screen(x,y)
{
	m_backgroundSprite.setTexture(Singleton::instance().getTexture("menu"));
	m_myButtonMap.emplace("play_btn", std::make_shared<PlayButton>());
	m_myButtonMap.emplace("help_btn", std::make_shared<HelpButton>());
	m_myButtonMap.emplace("exit_btn", std::make_shared<ExitButton>());
	

}
//-----------------------------------------------------------------------------
std::string Menu::runScreen(sf::RenderWindow & window, std::vector<std::shared_ptr<Player>>& PlayerVector)///////////////////////////////////////////////
{
	setButtonsPosition(window);
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)		//check which event is happening
			{
			case sf::Event::KeyPressed:				//if the user clicked on close
				if (event.key.code == sf::Keyboard::Escape)
					return "class Quit";
				else if (event.key.code == sf::Keyboard::F1)
					return "class Help";
			case sf::Event::MouseButtonReleased:
				return handleMouseReleased(event.mouseButton.x, event.mouseButton.y);

			case sf::Event::MouseMoved: // Mouse Moved
				mouseMoved(float(event.mouseMove.x), float(event.mouseMove.y), window);
				break;
			}
		}
		window.clear();
		draw(window);
		window.display();
	}
	return typeid(Menu).name();
}
//-----------------------------------------------------------------------------
void Menu::draw(sf::RenderWindow & window)
{
	window.draw(m_backgroundSprite);

	for(auto it : m_myButtonMap)
		window.draw(it.second->getSprite());
}
//-----------------------------------------------------------------------------
//this function sets the buttons location
void Menu::setButtonsPosition(sf::RenderWindow & window)
{
	sf::Vector2u windowSize = window.getSize();
	float scaleX = this->m_scaleX_background;
	float scaleY = this->m_scaleY_background;

	float c = 1;

	for (auto it = m_myButtonMap.rbegin() ; it != m_myButtonMap.rend() ; it++)
	{
	it->second->getSprite().setPosition((window.getSize().x / 1.5 - it->second->getSprite().getTexture()->getSize().x) / 2, 
		(window.getSize().y / 1.1 + (2.13*c) * it->second->getSprite().getTexture()->getSize().y) / 2);

	c++;
	}
}
//-----------------------------------------------------------------------------
//this function handles the mouse release event
std::string Menu::handleMouseReleased(float x, float y)
{
	for (auto it : m_myButtonMap)
	{
		if (it.second->getSprite().getGlobalBounds().contains(x, y))
			return it.second->getMyScreen();
	}
	return typeid(Menu).name();
}
//-----------------------------------------------------------------------------
//this function handles mouse moved function
void Menu::mouseMoved(float x, float y, sf::RenderWindow & window)
{
	for (auto it_button : m_myButtonMap)
	{
		if (it_button.second->getSprite().getGlobalBounds().contains(x, y))
			it_button.second->setOpacity(210);
		else
			it_button.second->setOpacity(255);
	}
}
