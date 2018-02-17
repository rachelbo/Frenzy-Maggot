//----------------------------------includes-----------------------------------
#include "doubleDispatch.h"

//-----------------------------------------------------------------------------
//this namespace
namespace {
	void headHead(GameObject& head1, GameObject& head2) 
	{
	}
	void linkHead(GameObject& link, GameObject& head)
	{
		Link& pLink = static_cast<Link&>(link);
		pLink.setIsExist(false);
	}
	void headLink(GameObject& head, GameObject& link) { linkHead(link, head); }
	void headAnt(GameObject& head, GameObject& ant)
	{
		Ant& pAnt = static_cast<Ant&>(ant);
		pAnt.setIsExist(false);
	}

	void linkRock(GameObject& link, GameObject& rock)
	{
		Rock& pRock = static_cast<Rock&>(rock);
	}
	void anthead(GameObject& ant, GameObject& head) { headAnt(head, ant); }
	void linkBomb(GameObject& link, GameObject& bomb) 
	{
		Link& pLink = static_cast<Link&>(link);
		pLink.setIsExist(false);
	}
	void bombLink(GameObject& bomb, GameObject& link) { linkBomb(link, bomb); }
	void antAnt  (GameObject& ant1, GameObject& ant2) {}
	void antRock(GameObject& ant, GameObject& rock) {}

	void rockRock(GameObject& rock1, GameObject& rock2)
	{
		
	}
	void antBomb (GameObject& ant, GameObject& bomb) 
	{
		Ant& pAnt = static_cast<Ant&>(ant);
		pAnt.setIsExist(false);
	}
	void rockBomb(GameObject& rock, GameObject& bomb)
	{
		Rock& pRock = static_cast<Rock&>(rock);
		pRock.setIsExist(false);
	}
	void headBomb(GameObject& head, GameObject& bomb)
	{
		Head& pHead = static_cast<Head&>(head);
		pHead.setIsExist(false);
	}
	void bombHead(GameObject& bomb, GameObject& head) { headBomb(head, bomb); }
	void linkAnt(GameObject& link, GameObject& ant)
	{
		Ant& pAnt = static_cast<Ant&>(ant);
	}
	void antLink(GameObject& ant, GameObject& link) { linkAnt(link, ant); }


	typedef void(*HitFunctionPtr)(GameObject&, GameObject&);
	typedef map< pair<string, string>, HitFunctionPtr > HitMap;

	HitMap initializeCollisionMap()
	{
		HitMap phm;
		phm[make_pair(typeid(Head).name(), typeid(Head).name())] =
			&headHead;
		phm[make_pair(typeid(Link).name(), typeid(Head).name())] =
			&linkHead;
		phm[make_pair(typeid(Head).name(), typeid(Link).name())] =
			&headLink;
		phm[make_pair(typeid(Head).name(), typeid(Ant).name())] =
			&headAnt;
		phm[make_pair(typeid(Head).name(), typeid(Rock).name())] =
			&linkRock;
		phm[make_pair(typeid(Ant).name(), typeid(Ant).name())] =
			&antAnt;
		phm[make_pair(typeid(Ant).name(), typeid(Head).name())] =
			&anthead;
		phm[make_pair(typeid(Ant).name(), typeid(Rock).name())] =
			&antRock;
		phm[make_pair(typeid(Ant).name(), typeid(Bomb).name())] =
			&antBomb;
		phm[make_pair(typeid(Rock).name(), typeid(Rock).name())] =
			&rockRock;
		phm[make_pair(typeid(Rock).name(), typeid(Bomb).name())] =
			&rockBomb;
		phm[make_pair(typeid(Head).name(), typeid(Bomb).name())] =
			&headBomb;
		phm[make_pair(typeid(Bomb).name(), typeid(Head).name())] =
			&bombHead;
		phm[make_pair(typeid(Link).name(), typeid(Bomb).name())] =
			&linkBomb;
		phm[make_pair(typeid(Bomb).name(), typeid(Link).name())] =
			&bombLink;
		phm[make_pair(typeid(Ant).name(), typeid(Link).name())] =
			&antLink;
		phm[make_pair(typeid(Link).name(), typeid(Ant).name())] =
			&linkAnt;
		return phm;
	}

	HitFunctionPtr lookup(const string& class1,
		const string& class2)
	{
		static HitMap collisionMap(initializeCollisionMap());
		HitMap::iterator mapEntry = collisionMap.find(make_pair(class1, class2));
		if (mapEntry == collisionMap.end())
			return 0;
		return (*mapEntry).second;
	}
}
//----------------------------------d-tor--------------------------------------
void doubleDispatch::processCollision(GameObject& object1, GameObject& object2)
{
	
	HitFunctionPtr phf = lookup(typeid(object1).name(),
		typeid(object2).name());
	if (phf)
		phf(object1, object2);
}