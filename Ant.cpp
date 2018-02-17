//----------------------------------includes-----------------------------------
#include "Ant.h"

//----------------------------------c-tor--------------------------------------
Ant::Ant(float x, float y)
{
	m_sprite.setTexture(Singleton::instance().getTexture("ant_left"));
	m_sprite.setPosition(sf::Vector2f(x, y));
}
//-----------------------------------------------------------------------------
//this function sets the direction of the ant
sf::Vector2f Ant::setAntDirection(float time, sf::Sprite& board)
{
	//choice of direction
	auto tempDirection = 0;
	sf::Vector2f setDirectionVec(sf::Vector2f(0,0));

	if (time - int(time) > 0.99)
	{
		tempDirection = m_myDirection;

			m_myDirection = std::rand() % 4;
	}

	switch (m_myDirection)
	{
	case 0:
		if (checkBoardCollision(board, sf::Vector2f(STEP, 0) + m_sprite.getPosition()))
		{
			setDirectionVec = sf::Vector2f(STEP, 0) + m_sprite.getPosition();
			m_sprite.setTexture(Singleton::instance().getTexture("ant_right"));
			scale_x = 54;
			scale_y = 40;
		}
		break;
	case 1:
		if (checkBoardCollision(board, sf::Vector2f(-STEP, 0) + m_sprite.getPosition()))
		{
			setDirectionVec = sf::Vector2f(-STEP, 0) + m_sprite.getPosition();
			m_sprite.setTexture(Singleton::instance().getTexture("ant_left"));
			scale_x = 54;
			scale_y = 40;
		}
		break;
	case 2:
		if (checkBoardCollision(board, sf::Vector2f(0, STEP) + m_sprite.getPosition()))
		{
			setDirectionVec = sf::Vector2f(0, STEP) + m_sprite.getPosition();
			m_sprite.setTexture(Singleton::instance().getTexture("ant_down"));
			scale_x = 40;
			scale_y = 54;
		}
		break;
	case 3:
		if (checkBoardCollision(board, sf::Vector2f(0, -STEP) + m_sprite.getPosition()))
		{
			setDirectionVec = sf::Vector2f(0, -STEP) + m_sprite.getPosition();
			m_sprite.setTexture(Singleton::instance().getTexture("ant_up"));
			scale_x = 40;
			scale_y = 54;
		}
		break;
	}

	return setDirectionVec;
}
//---------------------------------------------------------------------------
//this function sets the position of the sprite
void Ant::setPoition()
{
	m_sprite.setPosition(float(std::rand() % 1950), float(std::rand() % 1950));
	m_exist = true;
}
//---------------------------------------------------------------------------
//this function draws the ant
void Ant::drawAnt(sf::RenderWindow & window, float expTime)
{
	m_col++;

	m_sprite.setTextureRect(sf::IntRect((m_col % 4) * scale_x, 0, scale_x, scale_y));
	window.draw(m_sprite);
}