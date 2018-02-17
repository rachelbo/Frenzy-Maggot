#pragma once
//----------------------------------includes-----------------------------------
#include "MobileObject.h"

//----------------------------------class--------------------------------------
class Link : public MobileObject
{
public:
	Link(sf::Vector2f pos = sf::Vector2f(-300, -300), sf::Texture& body = Singleton::instance().getTexture("Bella body"));
	~Link();
	virtual sf::Vector2f getLinkLocation() const { return m_sprite.getPosition(); }
	virtual void setLinkLocation(sf::Vector2f pos, float angle);
	virtual void setAngle(float angle) { m_angle = angle; }
	virtual	float getAngle() { return m_angle; }
	void setLinkTextur(sf::Texture& texture);

	
protected:
	float m_angle{ 0.f };			//angle of the sprite
};
//----------------------------------class--------------------------------------
class Head : public Link
{
public:
	Head(sf::Vector2f pos = sf::Vector2f(1.f, 1.f), sf::Texture& head = Singleton::instance().getTexture("Bella head"));
	void setLinkLocation(sf::Vector2f pos, float angle) override;
	~Head() {}

protected:
	float m_angle{ 0.f };		//angle of the sprite
};



