//----------------------------------includes-----------------------------------
#include "Rock.h"

//static object reset
int Rock::m_index = 0;

//----------------------------------c-tor--------------------------------------
Rock::Rock(float x, float y)
{
	m_sprite.setTexture(Singleton::instance().getTexture("rock"));
	
	m_sprite.setTextureRect(sf::IntRect((m_index % 4) * 139, 0, 139, 110));
	m_sprite.setPosition(sf::Vector2f(x, y));

	++m_index;
}