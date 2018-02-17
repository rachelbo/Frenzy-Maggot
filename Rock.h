#pragma once
//----------------------------------includes-----------------------------------
#include "StaticObject.h"


//----------------------------------class--------------------------------------
class Rock : public StaticObject
{
public:
	Rock(float x, float y);
private:
	static int m_index;			//index of the sprite sheet
	sf::Sprite m_rocksSprite;	//rock sprite
};