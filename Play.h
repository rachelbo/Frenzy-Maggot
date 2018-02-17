#pragma once
//----------------------------------includes-----------------------------------
#include "Screen.h"
#include "Rock.h"
#include "Ant.h"
#include "doubleDispatch.h"
#include <algorithm>

#define NUMBER_OF_OBJECTS 20

//----------------------------------class--------------------------------------
class Play : public Screen
{
public:
	Play(float x, float y);
	bool canDropBomb(const vector<shared_ptr<Player>>::iterator& it);
	std::string runScreen(sf::RenderWindow & window, std::vector<std::shared_ptr<Player>>& PlayerVector);
	void draw(sf::RenderWindow& window);
	void setButtonsPosition(sf::RenderWindow & window) {}
	std::string handleMouseReleased(float x, float y) { return ""; }
	void setView(unsigned index, sf::RenderWindow& window);
	void checkPlayerCollition(std::vector<std::shared_ptr<Player>>::iterator playerIt, float dt);
	void checkAntCollision(std::map<unsigned, std::shared_ptr<Ant>>::iterator antIt, float dt);
	void checkBombCollision(std::map<float, std::shared_ptr<Bomb>>::iterator bombIt);
	void buildBoard();
	bool CheckCollitionbuildBoard(sf::Vector2f newPlace);
	sf::Vector2f getRandomLocation() { return sf::Vector2f(float(std::rand() % BOARD_SIZE), float(std::rand() % BOARD_SIZE)); }
	void endGame(sf::RenderWindow& window, int counter);

private:
	sf::Sprite m_board,											//board sprite
		m_youWonSprite,											//you wom sprite
		m_youLostSprite;										//you lost sprite
	doubleDispatch m_doubleDispatch;							//collisions
	std::vector<sf::View> m_view;								//views vector for each player
	std::vector<std::shared_ptr<Player>> m_playerVec;			//player vector
	std::map<unsigned, std::shared_ptr<Rock>> m_rocksMap;		//rocks map
	std::map<unsigned, std::shared_ptr<Ant>> m_antMap;			//ants map
	std::map<float, std::shared_ptr<Bomb>> m_bombMap;			//bomb map
	std::vector<sf::Vector2f> m_buildBoardData;					//vector of points
	sf::Clock m_bombClock, m_antClock;							//clocks

};
//---------------------------------------------------------------------------
//template function, chooses random places for maps of T objects
template <class T>
void chooseRandowStaticObjectPosition(std::map<unsigned, std::shared_ptr<T>>& objectMap)
{
	for (unsigned index = 0; index < NUMBER_OF_OBJECTS; index++)
	{
		float rand_x = float(std::rand() % 1950);
		float rand_y = float(std::rand() % 1950);

		if (!0 /*בדיקה אם יש התנגשות עם אובייקטים קיימים*/)
			objectMap.emplace(index, std::make_shared<T>(rand_x, rand_y));
		else
			index--;
	}
}