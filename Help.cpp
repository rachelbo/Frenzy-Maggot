//----------------------------------includes-----------------------------------
#include "Help.h"


//----------------------------------c-tor--------------------------------------
Help::Help(float x, float y) : Screen(x,y)
{
	m_backgroundSprite.setTexture(Singleton::instance().getTexture("help"));
}

//----------------------------------d-tor--------------------------------------
Help::~Help()
{
}
//-----------------------------------------------------------------------------
//this function handles mouse moved event
std::string Help::runScreen(sf::RenderWindow & window, std::vector<std::shared_ptr<Player>>& PlayerVector)
{
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
			}
		}
		window.clear();
		draw(window);
		window.draw(m_backgroundSprite);
		window.display();
	}
	return typeid(Help).name();
}
