#include "pch.h"
#include "FireFlower.h"
#include "Texture.h"

FireFlower::FireFlower()
	:PickUp(new Texture{ "Resources/PickUp.png" }, 2, 0.125f)
{
	m_Type = PickUpType::fireFlower;
}
