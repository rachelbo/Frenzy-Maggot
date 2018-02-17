#pragma once
//----------------------------------includes-----------------------------------
#include "Rock.h"
#include "Bomb.h"
#include "Link.h"
#include "Ant.h"

using namespace std;

//----------------------------------class--------------------------------------
class doubleDispatch {
public:
	doubleDispatch() {}
	~doubleDispatch() {}
	void processCollision(GameObject& object1,
					      GameObject& object2);
};


