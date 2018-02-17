#pragma once
//----------------------------------includes-----------------------------------
#include "Singleton.h"

//----------------------------------class--------------------------------------
class GameObject
{
public:
	GameObject();
	virtual void draw(sf::RenderWindow& window) { window.draw(m_sprite); }
	sf::Sprite getSprite() const { return m_sprite; }
	void setIsExist(bool exist) { m_exist = exist; }
	bool getIsExist() const { return m_exist; }

protected:
	bool m_exist = true;			//boolean member, true if the object should exist on the map
	sf::Sprite m_sprite;
};