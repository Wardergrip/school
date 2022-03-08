#include "pch.h"
#include "FireFlower.h"
#include "Texture.h"

FireFlower::FireFlower(const Point2f& pos)
	:PickUp(Type::fireFlower,new Texture{ "Resources/PowerUp.png" }, 2, 0.125f,3,2)
{
	m_Position = pos;
}
