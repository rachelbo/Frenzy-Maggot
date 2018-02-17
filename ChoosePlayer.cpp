//----------------------------------includes-----------------------------------
#include "ChoosePlayer.h"

//----------------------------------c-tor--------------------------------------
ChoosePlayer::ChoosePlayer(float x, float y, std::vector<std::shared_ptr<Player>>& PlayerVector) : Screen(x, y)
{
	m_backgroundSprite.setTexture(Singleton::instance().getTexture("play"));
	PlayerVector.emplace_back(std::make_shared<Player>(sf::Keyboard::A, sf::Keyboard::D, sf::Keyboard::W, sf::Keyboard::S, sf::Keyboard::LControl));
	PlayerVector.emplace_back(std::make_shared<Player>(sf::Keyboard::Left, sf::Keyboard::Right, sf::Keyboard::Up, sf::Keyboard::Down, sf::Keyboard::RControl));

	m_myButtonMap.emplace("NewGameButton", std::make_shared<NewGameButton>());
	m_myButtonMap.emplace("MenuButton", std::make_shared<MenuButton>());
}
//---------------------------------------------------------------------------
//this function handles the window
std::string ChoosePlayer::runScreen(sf::RenderWindow & window, std::vector<std::shared_ptr<Player>>& PlayerVector)
{
	sf::Clock clock;
	m_playerVec = PlayerVector;
	setButtonsPosition(window);
	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			switch (event.type)		//check which event is happening
			{
			case sf::Event::KeyPressed: //== sf::Keyboard::Escape:	//if the user clicked on close
				if (event.key.code == sf::Keyboard::Escape)
					return "class Menu";
				else if (event.key.code == sf::Keyboard::F1)
					return "class Help";

			case sf::Event::MouseButtonReleased:
				return handleMouseReleased(event.mouseButton.x, event.mouseButton.y);

			case sf::Event::MouseMoved: // Mouse Moved
				mouseMoved(float(event.mouseMove.x), float(event.mouseMove.y), window);
				break;
			}
		}
		float x = 0;
		for (auto it : PlayerVector)
		{
			it->eventHandler(x, 0, window);
			x += window.getSize().x / PlayerVector.size();
		}
		while (clock.getElapsedTime().asSeconds() < 0.1);		   //תזמון זמני, לחשוב על דרך טובה יותר
		clock.restart();										   //תזמון זמני, לחשוב על דרך טובה יותר

		window.clear();
		draw(window);
		window.display();
	}
	return typeid(ChoosePlayer).name();
}
//---------------------------------------------------------------------------
//this function draws all the elements
void ChoosePlayer::draw(sf::RenderWindow & window)
{
	window.draw(m_backgroundSprite);
	for (auto it : m_myButtonMap)
		window.draw(it.second->getSprite());

	for (auto it : m_playerVec)
		it->drawProfile(window);
}
//---------------------------------------------------------------------------
//this function sets buttons positions
void ChoosePlayer::setButtonsPosition(sf::RenderWindow & window)
{
	sf::Vector2u windowSize = window.getSize();

	float scaleX = this->m_scaleX_background;
	float scaleY = this->m_scaleY_background;

	float c = 2.5;

	for (auto it = m_myButtonMap.rbegin() ; it != m_myButtonMap.rend() ; it++)
	{
	it->second->getSprite().setPosition((window.getSize().x - it->second->getSprite().getTexture()->getSize().x) / 2, 
		(window.getSize().y / 3.5 + (2.25*c) * it->second->getSprite().getTexture()->getSize().y) / 2);

	c++;
	}
}
//---------------------------------------------------------------------------
//this function handles mouse released event
std::string ChoosePlayer::handleMouseReleased(float x, float y)
{
	for (auto it : m_myButtonMap)
	{
		if (it.second->getSprite().getGlobalBounds().contains(x, y))
			return it.second->getMyScreen();
	}
	return typeid(ChoosePlayer).name();
}
//---------------------------------------------------------------------------
//this function handles mouse moved event
void ChoosePlayer::mouseMoved(float x, float y, sf::RenderWindow & window)
{
	for (auto it_button : m_myButtonMap)
	{
		if (it_button.second->getSprite().getGlobalBounds().contains(x, y))
			it_button.second->setOpacity(210);
		else
			it_button.second->setOpacity(255);
	}
}