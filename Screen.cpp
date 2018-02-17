//----------------------------------includes-----------------------------------
#include "Screen.h"

//----------------------------------c-tor--------------------------------------
Screen::Screen(float x, float y) : m_scaleX_background(x), m_scaleY_background(y)
{
	m_backgroundSprite.setScale(x, y);
}
//----------------------------------d-tor--------------------------------------
Screen::~Screen()
{
}
