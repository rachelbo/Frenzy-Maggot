#pragma once
//----------------------------------includes-----------------------------------
#include "Singleton.h"
#include "Worm.h"
#include "doubleDispatch.h"

#define BAR_HEIGHT 20
#define BAR_WIDTH 300

//----------------------------------class--------------------------------------
class Player
{
public:
	Player(sf::Keyboard::Key left, sf::Keyboard::Key right, sf::Keyboard::Key up, sf::Keyboard::Key down, sf::Keyboard::Key bomb);
	sf::Vector2f setDirection(sf::Sprite boardSize, float dt);
	sf::Vector2f getLocation() const { return m_myWorm.getHeadLocation(); }
	sf::Vector2f getTailLocation() const { return m_myWorm.getTailLocation(); }
	void draw(sf::RenderWindow& window);
	void drawProfile(sf::RenderWindow& window);
	void playerLaser();
	void eventHandler(float x, float y, sf::RenderWindow& window);
	void setProfile(unsigned i);
	std::shared_ptr<Link> getHead() const { return m_myWorm.getHead(); }
	void movePlayer(sf::Vector2f vec, float dt)	{m_myWorm.setLocation(vec, m_direction, dt);}
	float getDirection() const { return m_direction; }
	void increaseWormSize();
	void decreaseWormSize();
	void checkLinksCollision(GameObject& object, doubleDispatch& funk);
	bool checkSkillKeys() { return sf::Keyboard::isKeyPressed(m_bombKey); }
	bool isStillAlive() { return m_myWorm.getHead()->getIsExist(); }
	void setOriginalPosition(int PlayerIndex);
	int getWormSize() { return  m_myWorm.getWormSize(); }
	int getMyScore()const { return m_myScore; }
	void increaseMyScore() { m_myScore++; }

private:
	unsigned profileIndex = 0;													//profile index
	sf::Sprite m_backgroundSprite;												//background sprite
	WormProfile m_myProfile = *(Singleton::instance().getWormProfile(0));		//palyer's profile
	Worm m_myWorm;																//worm
	unsigned int m_myScore = 0;													//score
	sf::Keyboard::Key m_leftKey;												//keys
	sf::Keyboard::Key m_rightKey;
	sf::Keyboard::Key m_upKey;
	sf::Keyboard::Key m_downKey;
	sf::Keyboard::Key m_bombKey;						
	float m_direction{ 0.f };													//direction of the worm
	float m_speed = float(LINK_SIZE*4);											//speed of the worm			
	float m_turnSpeed = 3.f;										
};