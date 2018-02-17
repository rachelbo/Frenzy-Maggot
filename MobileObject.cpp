//----------------------------------includes-----------------------------------
#include "MobileObject.h"


//----------------------------------c-tor--------------------------------------
MobileObject::MobileObject()
{
}

//----------------------------------d-tor--------------------------------------
MobileObject::~MobileObject()
{
}
//-----------------------------------------------------------------------------
//this function check board collisions
bool MobileObject::checkBoardCollision(sf::Sprite & board, sf::Vector2f& whereToMove)
{
	return (whereToMove.x >= 0 && whereToMove.y >= 0 && whereToMove.x <= board.getGlobalBounds().width - 50
		&& whereToMove.y <= board.getGlobalBounds().height - 50);
}
