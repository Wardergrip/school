#include "pch.h"
#include "Mushroom.h"
#include "Texture.h"
#include "Level.h"
#include "utils.h"
#include <iostream>
using namespace utils;

Mushroom::Mushroom(PickUpType type, Level* levelReference, const Point2f& pos)
	:PickUp(new Texture{ "Resources/PowerUp.png" }, 1, 0.125f,3,int(type))
	,m_LevelRef{levelReference}
	,m_Velocity{100,0}
{
	if (type != PickUpType::normalMushroom && type != PickUpType::oneUpMushroom) std::cout << "Wrong Mushroom type!\n";
	m_Position = pos;
	m_Rect.width = m_Rect.width / 2;
}

void Mushroom::Update(float elapsedSec)
{
	HitInfo HI;
	Vector2f g{0,-981};
	Rectf r{ m_Position.x,m_Position.y,m_Rect.width,m_Rect.height };
	if (m_LevelRef->IsOnTop(r, HI))
	{
		m_Velocity.y = 0;
		m_Position.y += (1 - HI.lambda);
	}
	else m_Velocity += g * elapsedSec;
	if (m_LevelRef->IsHorizontallyTouching(r))
	{
		m_Velocity.x = -m_Velocity.x;
	}

	m_Position += m_Velocity * elapsedSec;
}
