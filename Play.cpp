//----------------------------------includes-----------------------------------
#include "Play.h"
#include <Windows.h>

//----------------------------------c-tor--------------------------------------
Play::Play(float x, float y) : Screen(x, y)
{
	m_backgroundSprite.setTexture(Singleton::instance().getTexture("play"));
	//set game sprite
	m_board.setTexture(Singleton::instance().getTexture("ground"));
	m_youWonSprite.setTexture(Singleton::instance().getTexture("you_won"));
	m_youWonSprite.setOrigin(m_youWonSprite.getTextureRect().width / 2, m_youWonSprite.getTextureRect().height / 2);
	m_youLostSprite.setTexture(Singleton::instance().getTexture("you_lost"));
	m_youLostSprite.setOrigin(m_youLostSprite.getTextureRect().width / 2, m_youLostSprite.getTextureRect().height / 2);
	
	//set game view
	m_view.resize(2);
	m_view[0].setViewport(sf::FloatRect(0.01f, 0.02f, 0.49f, 0.8f));
	m_view[1].setViewport(sf::FloatRect(0.51f, 0.02f, 0.48f, 0.8f));
	m_view[0].getSize();
}

//---------------------------------------------------------------------------
//this function handles mouse moved event
std::string Play::runScreen(sf::RenderWindow & window, std::vector<std::shared_ptr<Player>>& PlayerVector)
{
	sf::Clock clock;
	std::srand(std::time(0));
	float dropBombTime = 0;

	//set player data
	m_playerVec = PlayerVector;
	for (int i = 0; i < m_playerVec.size(); ++i)
		m_playerVec[i]->setOriginalPosition(i);

	buildBoard();

	while (window.isOpen())
	{
		auto dt(clock.restart().asSeconds());
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)		//check which event is happening
			{
			case sf::Event::KeyPressed:			//if the user clicked on close
				if (event.key.code == sf::Keyboard::Escape)
				{
					window.setView(window.getDefaultView());
					return "class Menu";
				}
				if (event.key.code == sf::Keyboard::F1)
					return "class Help";
				break;
			default:;
			}
		}
		int counter = 0;
		for (auto it = m_playerVec.begin(); it != m_playerVec.end(); ++it)
		{
			if (!(*it)->isStillAlive())
			{
				(*it)->increaseMyScore();
				endGame(window, counter);
				return "class Menu";
			}

			if ((*it)->checkSkillKeys() && ((m_bombClock.getElapsedTime().asSeconds() - dropBombTime) > 0.5))
			{
				if (canDropBomb(it))
				{
					dropBombTime = m_bombClock.getElapsedTime().asSeconds();
					m_bombMap.emplace(dropBombTime, std::make_shared<Bomb>((*it)->getTailLocation()));
				}
			}
			checkPlayerCollition(it, dt);
				counter++;
		}

		for (auto it = m_antMap.begin(); it != m_antMap.end(); ++it)
			checkAntCollision(it, m_antClock.getElapsedTime().asSeconds());

		window.clear();
		draw(window);
		window.display();
	}
	return typeid(Play).name();
}
//---------------------------------------------------------------------------
//this function draws the elements on the window
void Play::draw(sf::RenderWindow & window)
{
	window.setView(window.getDefaultView());
	window.draw(m_backgroundSprite);

	for (unsigned i = 0; i < m_playerVec.size(); i++)
		setView(i, window);
}
//---------------------------------------------------------------------------
//this function sets the view of the players
void Play::setView(unsigned index, sf::RenderWindow& window)
{
	m_view[index].reset(sf::FloatRect(0, 0, 1250, 1250));

	if (m_playerVec[index]->getLocation().x > m_view[index].getCenter().x)
		if (m_playerVec[index]->getLocation().x < m_board.getGlobalBounds().width - (m_view[index].getSize().x) / 2)
			if (m_playerVec[index]->getLocation().y > m_view[index].getCenter().y)
				if (m_playerVec[index]->getLocation().y < m_board.getGlobalBounds().height - (m_view[index].getSize().y) / 2)
					m_view[index].setCenter(m_playerVec[index]->getLocation());
				else
					m_view[index].setCenter(m_playerVec[index]->getLocation().x, m_board.getGlobalBounds().height - (m_view[index].getSize().y) / 2);
			else
				m_view[index].setCenter(m_playerVec[index]->getLocation().x, m_view[index].getCenter().y);
		else if (m_playerVec[index]->getLocation().y > m_view[index].getCenter().y)
			if (m_playerVec[index]->getLocation().y < m_board.getGlobalBounds().height - (m_view[index].getSize().y) / 2)
				m_view[index].setCenter(m_board.getGlobalBounds().width - (m_view[index].getSize().x) / 2, m_playerVec[index]->getLocation().y);
			else
				m_view[index].setCenter(m_board.getGlobalBounds().width - (m_view[index].getSize().x) / 2, m_board.getGlobalBounds().height - (m_view[index].getSize().y) / 2);
		else
			m_view[index].setCenter(m_board.getGlobalBounds().width - (m_view[index].getSize().x) / 2, m_view[index].getCenter().y);
	else if (m_playerVec[index]->getLocation().y > m_view[index].getCenter().y)
		if (m_playerVec[index]->getLocation().y < m_board.getGlobalBounds().height - (m_view[index].getSize().y) / 2)
			m_view[index].setCenter(m_view[index].getCenter().x, m_playerVec[index]->getLocation().y);
		else
			m_view[index].setCenter(m_view[index].getCenter().x, m_board.getGlobalBounds().height - (m_view[index].getSize().y) / 2);
	else
		m_view[index].setCenter(m_view[index].getCenter().x, m_view[index].getCenter().y);
	
	window.setView(m_view[index]);
	window.draw(m_board);

	//draw player
	for (auto it : m_playerVec)
		it->draw(window);

	//draw rock
	for (auto& x = m_rocksMap.begin(); x != m_rocksMap.end();)
		if ((*x).second->getIsExist())
		{
			(*x).second->draw(window);
			++x;
		}
		else
			x = m_rocksMap.erase(x);

	//draw ant
	for (auto ant : m_antMap)
	{
		float currTime = m_antClock.getElapsedTime().asSeconds();
		if (ant.second->getIsExist())
			ant.second->drawAnt(window,currTime);
		else
			ant.second->setPoition();
	}

	//draw bomb&explosion
	for (auto& bombIt = m_bombMap.begin(); bombIt != m_bombMap.end();)
	{
		float currTime = m_bombClock.getElapsedTime().asSeconds();

		if ((currTime - (bombIt->first) > 2) && (currTime - (bombIt->first) <= 3))
		{
			checkBombCollision(bombIt);
			bombIt->second->drawExplosion(window, currTime);
			++bombIt;
		}
		else if(currTime - (bombIt->first) > 3)
			bombIt = m_bombMap.erase(bombIt);
		else
		{
			bombIt->second->drawBomb(window, currTime);
			++bombIt;
		}
	}
}
//---------------------------------------------------------------------------
//this function checks player collision
void Play::checkPlayerCollition(std::vector<std::shared_ptr<Player>>::iterator playerIt, float dt)
{
	sf::Sprite tempNext = (*playerIt)->getHead()->getSprite();
	sf::Vector2f offSet = (*playerIt)->setDirection(m_board, dt);
	sf::Vector2f whereToMove = (*playerIt)->getLocation() + offSet;
	tempNext.setPosition(whereToMove);
	auto direction = (*playerIt)->getDirection();
	tempNext.setRotation(direction * 180 / static_cast<float>(M_PI));

	if (whereToMove == sf::Vector2f(0, 0))
		return;

	for (auto rock : m_rocksMap)
	{
		if (rock.second->getSprite().getGlobalBounds().intersects(tempNext.getGlobalBounds()))
		{
			m_doubleDispatch.processCollision(*(*playerIt)->getHead(), *rock.second);
			return;
		}
	}

	for (auto ant : m_antMap)
	{
		if (ant.second->getSprite().getGlobalBounds().intersects(tempNext.getGlobalBounds()))
		{
			m_doubleDispatch.processCollision(*(*playerIt)->getHead(), *ant.second);
			(*playerIt)->increaseWormSize();
			return;
		}
		else
			(*playerIt)->checkLinksCollision(*ant.second, m_doubleDispatch);
	}

	for (auto it = m_playerVec.begin(); it != m_playerVec.end(); ++it)
		if (playerIt != it && (*it)->getHead()->getSprite().getGlobalBounds().intersects(tempNext.getGlobalBounds()))
		{
			m_doubleDispatch.processCollision(*(*playerIt)->getHead(), *(*it)->getHead());
			return;
		}

	Head tempHead;
	tempHead.setLinkLocation(tempNext.getPosition(), dt);
	for (auto it = m_playerVec.begin(); it != m_playerVec.end(); ++it)
		if (playerIt != it )
		{
			(*it)->checkLinksCollision(tempHead, m_doubleDispatch);
		}

	(*playerIt)->movePlayer(offSet, dt);
}

//---------------------------------------------------------------------------
//this function check ant collisions  
void Play::checkAntCollision(std::map<unsigned, std::shared_ptr<Ant>>::iterator antIt, float time)
{
	sf::Vector2f whereToMove = (*antIt).second->setAntDirection(time, m_board);
	sf::Sprite tempNext = (*antIt).second->getSprite();
	tempNext.setPosition(whereToMove);

	if (whereToMove == sf::Vector2f(0, 0))
		return;

	for (auto it = m_antMap.begin(); it != m_antMap.end(); ++it)
		{
			if (antIt != it && it->second->getSprite().getGlobalBounds().intersects(tempNext.getGlobalBounds()))
			{
				return;
			} 
		}

	for (auto rock : m_rocksMap)
		if (tempNext.getGlobalBounds().intersects(rock.second->getSprite().getGlobalBounds()))
		{
			if (rock.second->getSprite().getGlobalBounds().intersects(tempNext.getGlobalBounds()))
			{
				return;
			}
		}

	antIt->second->moveAnt(whereToMove);
}
//---------------------------------------------------------------------------
//this function check bomb collision
void Play::checkBombCollision(std::map<float, std::shared_ptr<Bomb>>::iterator bombIt)
{
	for (auto ant : m_antMap)
	{
		if (ant.second->getSprite().getGlobalBounds().intersects(bombIt->second->getexpSprite().getGlobalBounds()))
		{
			m_doubleDispatch.processCollision(*ant.second, *bombIt->second);
			return;
		}
	}

	for (auto rock : m_rocksMap)
	{
		if (rock.second->getSprite().getGlobalBounds().intersects(bombIt->second->getexpSprite().getGlobalBounds()))
		{
			m_doubleDispatch.processCollision(*rock.second, *bombIt->second);
			return;
		}
	}

	for (auto it = m_playerVec.begin(); it != m_playerVec.end(); ++it)
		(*it)->checkLinksCollision(*bombIt->second, m_doubleDispatch);
}
//---------------------------------------------------------------------------
//this function bulids all the relevent elements on the board at the start of 
//the game
void Play::buildBoard()
{
	m_antMap.clear();
	m_bombMap.clear();
	m_rocksMap.clear();
	m_buildBoardData.clear();

	auto temp = getRandomLocation();
	for (unsigned index = 0; index < NUMBER_OF_OBJECTS; index++)
	{
		while (!CheckCollitionbuildBoard(temp))
			temp = getRandomLocation();
		m_antMap.emplace(index, std::make_shared<Ant>(temp.x, temp.y));
	}

	for (unsigned index = 0; index < NUMBER_OF_OBJECTS; index++)
	{
		while (!CheckCollitionbuildBoard(temp))
			temp = getRandomLocation();
		m_rocksMap.emplace(index, std::make_shared<Rock>(temp.x, temp.y));
	}
}
//---------------------------------------------------------------------------
//checks collision
bool Play::CheckCollitionbuildBoard(sf::Vector2f newPlace)
{
	for (size_t i = 0; i < m_buildBoardData.size(); i++)
		if (abs(newPlace.x - m_buildBoardData[i].x) <= LINK_SIZE &&
			abs(newPlace.x - m_buildBoardData[i].x) >= 0 &&
			abs(newPlace.y - m_buildBoardData[i].y) <= LINK_SIZE &&
			abs(newPlace.y - m_buildBoardData[i].y) >= 0
			)
			return false;

	m_buildBoardData.emplace_back(newPlace);
	return true;
}
//---------------------------------------------------------------------------
//this function handles the end of the game, when one of the player loses
void Play::endGame(sf::RenderWindow & window, int counter)
{
	m_youLostSprite.setPosition(m_view[counter].getCenter());
	window.setView(m_view[counter]);
	window.draw(m_youLostSprite);
	m_youWonSprite.setPosition(m_view[(counter + 1) % 2].getCenter());
	window.setView(m_view[(counter + 1) % 2]);
	window.draw(m_youWonSprite);
	window.display();
	Sleep(3000);
	window.setView(window.getDefaultView());
	m_playerVec[counter]->getHead()->setIsExist(true);
}
//---------------------------------------------------------------------------
//this function checks if the player can drop the game
bool Play::canDropBomb(const vector<shared_ptr<Player>>::iterator& it)
{
	if((*it)->getWormSize() > 1)
	{
		(*it)->decreaseWormSize();
		return true;
	}
	return false;
}