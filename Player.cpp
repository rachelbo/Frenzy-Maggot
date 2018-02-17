//----------------------------------includes-----------------------------------
#include "Player.h"
#include "Buttons.h"

//----------------------------------c-tor--------------------------------------
Player::Player(sf::Keyboard::Key left, sf::Keyboard::Key right, sf::Keyboard::Key up, sf::Keyboard::Key down, sf::Keyboard::Key bomb) //להוסיף מהירות
	:m_leftKey(left), m_rightKey(right), m_upKey(up), m_downKey(down), m_bombKey(bomb)
{
	m_myWorm.setWormTextur(m_myProfile.wormHeadTexture, m_myProfile.wormBodyTexture);
	setProfile(0);
}
//---------------------------------------------------------------------------
//this function set direction of the worm
sf::Vector2f Player::setDirection(sf::Sprite boardSize, float dt)
{
	if (sf::Keyboard::isKeyPressed(m_leftKey))
		m_direction -= m_turnSpeed * dt;
	if (sf::Keyboard::isKeyPressed(m_rightKey))
		m_direction += m_turnSpeed * dt;

	auto xOffset = m_speed * dt * std::cos(m_direction);
	auto yOffset = m_speed * dt * std::sin(m_direction);
	sf::Vector2f whereToMove = m_myWorm.getHeadLocation() + sf::Vector2f(xOffset, yOffset);

	if (m_myWorm.checkBoardCollision(boardSize, whereToMove))

		return sf::Vector2f(xOffset, yOffset);
	else
		return sf::Vector2f(0, 0);
}

//---------------------------------------------------------------------------
//this function draws the player's worm
void Player::draw(sf::RenderWindow & window)
{
	m_myProfile.wormSize = m_myWorm.getWormSize();
	m_myWorm.draw(window); 
}
//---------------------------------------------------------------------------
void Player::playerLaser()
{
}
//---------------------------------------------------------------------------
//this function draws the player's profile
void Player::drawProfile(sf::RenderWindow & window)
{
	window.draw(m_backgroundSprite);
}
//---------------------------------------------------------------------------
//this function andles player's event
void Player::eventHandler(float x, float y, sf::RenderWindow& window)
{
	m_backgroundSprite.setPosition(x + 150, y + 10);
	//m_backgroundSprite.setTextureRect(sf::IntRect(0, 0, 753, 800));
	m_backgroundSprite.setTexture(m_myProfile.wormProfileTexture);

	if (sf::Keyboard::isKeyPressed(m_leftKey))
		setProfile((--profileIndex) % (Singleton::instance().getWormProfileSize()));
	else if (sf::Keyboard::isKeyPressed(m_rightKey))
		setProfile((profileIndex++) % Singleton::instance().getWormProfileSize());
	drawProfile(window);
}
//---------------------------------------------------------------------------
//this function sets the worm's profile
void Player::setProfile(unsigned i)
{
	m_myProfile = *(Singleton::instance().getWormProfile(i));
	m_backgroundSprite.setTexture(m_myProfile.wormProfileTexture);
	m_myWorm.setWormSize(m_myProfile);
	m_myWorm.setLaser(m_myProfile.laser);
	m_myWorm.setBost(m_myProfile.boost);
	m_myWorm.setWormTextur(m_myProfile.wormHeadTexture, m_myProfile.wormBodyTexture);
}
//---------------------------------------------------------------------------
//this function increases the worms size
void Player::increaseWormSize()
{
	m_myProfile.wormSize++;
	m_myWorm.setWormSize(m_myProfile);
}
//---------------------------------------------------------------------------
//this function decreases the worms size
void Player::decreaseWormSize()
{
	m_myProfile.wormSize--;
	m_myWorm.setWormSize(m_myProfile);
}

//---------------------------------------------------------------------------
//this function checks link collision
void Player::checkLinksCollision(GameObject& object, doubleDispatch& funk)
{
	m_myWorm.checkLinksCollision(object, funk);
}
//---------------------------------------------------------------------------
//this function sets the origin of the position
void Player::setOriginalPosition(int PlayerIndex)
{
	m_myWorm.setOriginalPosition(float(std::rand() % (BOARD_SIZE+50)/2 + PlayerIndex*BOARD_SIZE / 2 + 25),
							     float(std::rand() % (BOARD_SIZE+50)) + 25);
	m_myWorm.setWormSize(m_myProfile);
}
