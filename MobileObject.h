#pragma once
//----------------------------------includes-----------------------------------
#include "GameObject.h"

//----------------------------------class--------------------------------------
class MobileObject : public GameObject
{
public:
	MobileObject();
	~MobileObject();
	bool checkBoardCollision(sf::Sprite& board, sf::Vector2f& whereToMove);
	
};

