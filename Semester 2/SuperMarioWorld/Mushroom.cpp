#include "pch.h"
#include "Mushroom.h"
#include "Texture.h"
#include "Level.h"
#include "utils.h"
using namespace utils;

Mushroom::Mushroom(Type type, Level* levelReference, const Point2f& pos)
	:PickUp(type, new Texture{ "Resources/PowerUp.png" }, 1, 0.125f,3,int(type))
	,m_LevelRef{levelReference}
	,m_Velocity{100,0}
{
	if (type != Type::normalMushroom && type != Type::oneUpMushroom) throw "Wrong Mushroom type!";
	m_Position = pos;
}

void Mushroom::Update(float elapsedSec)
{
	HitInfo HIv{},HIh{};
	Rectf r{ m_Position.x,m_Position.y,m_Rect.width,m_Rect.height };
	if (m_LevelRef->IsOnTop(r, HIv, m_Velocity))
	{
		m_Velocity.y = 0;
		m_Position.y += (1 - HIv.lambda);
	}
	else m_Velocity += m_Gravity * elapsedSec;
	if (m_LevelRef->IsHorizontallyTouching(r, HIh, m_Velocity,(m_Velocity.x) / std::abs(m_Velocity.x)))
	{
		m_Velocity.x = -m_Velocity.x;
	}

	m_Position += m_Velocity * elapsedSec;
}
