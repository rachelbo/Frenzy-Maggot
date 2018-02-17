//----------------------------------includes-----------------------------------
#include "Worm.h"

//----------------------------------c-tor--------------------------------------
Worm::Worm()
{
	m_wormList.emplace_back(std::make_shared<Head>(sf::Vector2f(std::rand()%500, std::rand()%500)));

}
//---------------------------------------------------------------------------
//this function draws the links of the worm
void Worm::draw(sf::RenderWindow & window)
{
	checkDeadLinks();
	for (auto it = m_wormList.rbegin(); it != m_wormList.rend(); ++it)
		(*it)->draw(window);

}
//---------------------------------------------------------------------------
//this function sets the location of the worm
void Worm::setLocation(sf::Vector2f pos, float angle, float dt)
{
	int size = STEP;
	//מיקום הראש
	auto preIt = m_wormList.begin();								 
	sf::Vector2f preVec = (*preIt)->getLinkLocation();				
	(*preIt)->setLinkLocation( pos+ preVec, angle);					

	//עדכון התנועה הבאה של החוליות
	for(int index = m_points.size()-1; index >= 1; --index)			
		m_points[index] = m_points[index-1];	
	m_points[0] =(std::pair< sf::Vector2f, float>(pos + preVec, angle));

	// תנועה של החוליות
	for (auto it = ++m_wormList.begin(); it != m_wormList.end(); ++it, size += STEP)
			(*it)->setLinkLocation(m_points[size].first, m_points[size].second);

}
//---------------------------------------------------------------------------
void Worm::setColor(std::string color)
{
	//הפונקציה מקבלת סטרינג של sf::color ומשנה את צבע הלינקים או הראש
}
//---------------------------------------------------------------------------
void Worm::setWormSize(WormProfile& profile)
{
	if(m_wormList.size()>profile.wormSize)
		m_wormList.resize(profile.wormSize);
	
	else if (m_wormList.size() < profile.wormSize)
	{
		while (m_wormList.size() < profile.wormSize)
		{
		m_wormList.emplace_back(std::make_shared<Link>(sf::Vector2f(-300, -300), profile.wormBodyTexture));//חוליה חדשה נוצרת מחוץ למסך
		}
	}
	profile.wormSize = m_wormList.size();
	m_points.resize(m_wormList.size()*STEP);

	for (int index = m_points.size() - 1; index >= 1; --index)
		m_points[index] = m_points[index - 1];
}
//---------------------------------------------------------------------------
//this function cehck collision of the worm
void Worm::checkLinksCollision(GameObject& object, doubleDispatch& funk)
{
	for (auto it = m_wormList.begin(); it != m_wormList.end(); ++it)
		if(object.getSprite().getGlobalBounds().intersects((*it)->getSprite().getGlobalBounds()))
			funk.processCollision(object, *(*it));
}
//---------------------------------------------------------------------------
//this set original position
void Worm::setOriginalPosition(float x, float y)
{
	(*m_wormList.begin())->setLinkLocation(sf::Vector2f(x, y), 0);
}
//---------------------------------------------------------------------------
//this function sets the worm texture
void Worm::setWormTextur( sf::Texture& head, sf::Texture& body)
{
	auto it = m_wormList.begin();
	(*it)->setLinkTextur(head);

	for (auto it = ++m_wormList.begin(); it != m_wormList.end(); ++it)
		(*it)->setLinkTextur(body);
}

//---------------------------------------------------------------------------
//this function checks dead links
void Worm::checkDeadLinks()
{
	for (auto it = m_wormList.begin(); it != m_wormList.end(); ++it)
		if (!(*it)->getIsExist() && it != m_wormList.begin())
			while( it != m_wormList.end())
				it = m_wormList.erase(it);
}