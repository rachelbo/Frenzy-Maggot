#include "EndLevel.h"

EndLevel::EndLevel(float x, float y) : Screen(x,y)
{
	m_backgroundSprite.setTexture(Singleton::instance().getTexture("end_level"));

	m_myButtonMap.emplace("play_btn", std::make_shared<PlayButton>());
	m_myButtonMap.emplace("exit_btn", std::make_shared<ExitButton>());
}

EndLevel::~EndLevel()
{
}

std::string EndLevel::runScreen(sf::RenderWindow& window, std::vector<std::shared_ptr<Player>>& PlayerVector)
{
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
	return typeid(EndLevel).name();
}

void EndLevel::draw(sf::RenderWindow& window)
{
	window.draw(m_backgroundSprite);

	for (auto it : m_myButtonMap)
		window.draw(it.second->getSprite());
}

void EndLevel::setButtonsPosition(sf::RenderWindow& window)
{
	sf::Vector2u windowSize = window.getSize();

	float c = 1;

	for (auto it = m_myButtonMap.rbegin(); it != m_myButtonMap.rend(); ++it)
	{
		it->second->getSprite().setPosition((window.getSize().x / 2) ,	(window.getSize().y / 2)+ it->second->getSprite().getGlobalBounds().height*c+100);
		c++;
	}
}

std::string EndLevel::handleMouseReleased(float x, float y)
{
	for (auto it : m_myButtonMap)
	{
		if (it.second->getSprite().getGlobalBounds().contains(x, y))
			return it.second->getMyScreen();
	}
	return typeid(EndLevel).name();
}

void EndLevel::mouseMoved(float x, float y, sf::RenderWindow & window)
{
	for (auto it_button : m_myButtonMap)
	{
		if (it_button.second->getSprite().getGlobalBounds().contains(x, y))
			it_button.second->setOpacity(210);
		else
			it_button.second->setOpacity(255);
	}
}
