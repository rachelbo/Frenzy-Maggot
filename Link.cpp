//----------------------------------includes-----------------------------------
#include "Link.h"

//----------------------------------c-tor--------------------------------------
Link::Link(sf::Vector2f pos, sf::Texture& body)
{
	m_sprite.setTexture(body);
	m_sprite.setOrigin(m_sprite.getTextureRect().width / 2, m_sprite.getTextureRect().height / 2);
	m_sprite.setPosition(pos);
}
//----------------------------------d-tor--------------------------------------
Link::~Link()
{
}
//-----------------------------------------------------------------------------
//this function sets the links location
void Link::setLinkLocation(sf::Vector2f pos, float angle)
{
	m_sprite.setPosition(pos);
	m_sprite.setRotation(angle * 180 / static_cast<float>(M_PI));
	m_angle = angle;
}

//-----------------------------------------------------------------------------
//this function sets the link texture
void Link::setLinkTextur(sf::Texture& texture)
{
	texture.setSmooth(true);
	m_sprite.setTexture(texture);
}
//-----------------------------------c_tor--------------------------------------
Head::Head(sf::Vector2f pos, sf::Texture& head)
{
	m_sprite.setTexture(head);
	//m_sprite.setTextureRect(sf::IntRect(0, 0, 90, 95));
	m_sprite.setOrigin(m_sprite.getTextureRect().width / 2, m_sprite.getTextureRect().height / 2);
	m_sprite.setPosition(pos);
}
//-----------------------------------------------------------------------------
//this function sets the head link location
void Head::setLinkLocation(sf::Vector2f pos, float angle)
{
	m_sprite.setPosition(pos);
	m_sprite.setRotation(angle * 180 / static_cast<float>(M_PI));
	m_angle = angle * 180 / static_cast<float>(M_PI);
}
