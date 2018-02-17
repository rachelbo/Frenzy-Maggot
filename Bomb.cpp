//----------------------------------includes-----------------------------------
#include "Bomb.h"

//----------------------------------c-tor--------------------------------------
Bomb::Bomb(sf::Vector2f pos)
{
	//set textures and positions
	m_sprite.setTexture(Singleton::instance().getTexture("bomb"));
	m_explosionSprite.setTexture(Singleton::instance().getTexture("explosion"));
	m_sprite.setPosition(pos);
	m_explosionSprite.setTextureRect(sf::IntRect(0,0,384, 384));
	m_explosionSprite.setOrigin(m_explosionSprite.getTextureRect().width / 2, 
		m_explosionSprite.getTextureRect().height / 2);
	m_explosionSprite.setPosition(pos);
}
//-----------------------------------------------------------------------------
//this function draws the explosion
void Bomb::drawExplosion(sf::RenderWindow& window, float expTime)
{
	static float dropTime = expTime;

	//change sprite
	if (expTime - dropTime > 0.0625)
	{
		dropTime = expTime;

		if (m_row < 4)
		{
			if (m_col < 3)
			{
				m_col++;
			}
			else
			{
				m_row++;
				m_col = 0;
			}
		}
	}
	//set sprite
	m_explosionSprite.setTextureRect(sf::IntRect(m_col * 384, m_row * 384, 384, 384));
	//draw window
	window.draw(m_explosionSprite);


}
//-----------------------------------------------------------------------------
//this function draw the bomb
void Bomb::drawBomb(sf::RenderWindow & window, float expTime)
{
	static float bombTime = expTime;

	if (expTime - bombTime > 0.285714)
	{
		bombTime = expTime;
		if (m_col < 6)
			m_col++;
	}
	m_sprite.setTextureRect(sf::IntRect(m_col * 77.8571, 0, 77.8571, 80));
	m_sprite.setOrigin(m_sprite.getTextureRect().width / 2, m_sprite.getTextureRect().height / 2);
	window.draw(m_sprite);
}
//----------------------------------d-tor--------------------------------------
Bomb::~Bomb()
{
}
