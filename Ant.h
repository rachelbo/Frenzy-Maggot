#pragma once
//----------------------------------includes-----------------------------------
#include "MobileObject.h"
#define STEP 1

//----------------------------------class--------------------------------------
class  Ant : public MobileObject
{
public:
	Ant(float x, float y);
	~Ant(){}
	sf::Vector2f setAntDirection(float time, sf::Sprite& board);
	void moveAnt(sf::Vector2f vec) { m_sprite.setPosition(vec); }
	void setPoition();
	void drawAnt(sf::RenderWindow& window, float expTime);
		
private:
	unsigned m_myDirection = std::rand() % 4;	//ants movement direction
	int m_col = 0;								//col of sprite
	int scale_x = 54;							//x scale of sprite
	int scale_y = 40;							//y scale of sprite
};