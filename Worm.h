#pragma once
//----------------------------------includes-----------------------------------
#include "Singleton.h"
#include "Link.h"
#include "doubleDispatch.h"

#define  STEP LINK_SIZE*0.5
//----------------------------------class--------------------------------------
class Worm
{
public:
	Worm();
	void draw(sf::RenderWindow& window);
	void setLocation(sf::Vector2f pos, float angle, float dt);
	sf::Vector2f getHeadLocation() const { return (*m_wormList.begin())->getLinkLocation(); }
	sf::Vector2f getTailLocation() const { return (*m_wormList.rbegin())->getLinkLocation(); }
	unsigned& getBost() { return m_bost; }
	unsigned& getLaser() { return m_laser; }
	void setColor(std::string color);
	void setLaser(unsigned laser) { m_laser = laser; }
	void setBost(unsigned bost) { m_bost = bost; }
	void setWormSize(WormProfile& profile);
	bool checkBoardCollision(sf::Sprite& board, sf::Vector2f& whereToMove) { return (*m_wormList.begin())->checkBoardCollision(board, whereToMove); }
	std::shared_ptr<Link> getHead() const { return (*m_wormList.begin()); }
	size_t getWormSize() { return  m_wormList.size(); }
	void checkLinksCollision(GameObject& head, doubleDispatch& funk);
	void setOriginalPosition(float x, float y);
	void setWormTextur(sf::Texture& head, sf::Texture& body);
	void checkDeadLinks();
	
protected:
	unsigned m_bost = 35;									//boost
	unsigned m_laser = 69;									//laser
	std::list<std::shared_ptr<Link>> m_wormList;
	std::vector<std::pair<sf::Vector2f, float>> m_points;
};

