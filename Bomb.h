#pragma once
//----------------------------------includes-----------------------------------
#include "StaticObject.h"

//----------------------------------class--------------------------------------
class Bomb : public StaticObject
{
public:
	Bomb(sf::Vector2f pos);
	void drawExplosion(sf::RenderWindow& window, float expTime);
	void drawBomb(sf::RenderWindow& window, float expTime);
	sf::Sprite getexpSprite() const { return m_explosionSprite; }
	~Bomb();

private:
	sf::IntRect m_rect;					//int rectangle
	sf::Sprite m_explosionSprite;		//sprite of explosion
	int m_row = 0, m_col = 0;			//row and col of the sprite
};

