#include "pch.h"
#include "FireFlower.h"
#include "Texture.h"

FireFlower::FireFlower(const Point2f& pos)
	:PickUp(new Texture{ "Resources/PowerUp.png" }, 2, 0.125f,2,1)
{
	m_Type = PickUpType::fireFlower;
	m_Position = pos;
}
