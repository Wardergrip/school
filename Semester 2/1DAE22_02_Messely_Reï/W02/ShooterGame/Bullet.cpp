#include "pch.h"
#include "Bullet.h"
#include "Enemy.h"
#include "utils.h"

Bullet::Bullet(float width, float height)
	:m_Center{}
	,m_Width{width}
	,m_Height{height}
	,m_Velocity{ Vector2f{} }
	,m_Boundaries{}
	,m_IsActivated(false)
{
}

Bullet::Bullet()
	:Bullet(0,0)
{
}

void Bullet::Draw() const
{
	if (!m_IsActivated) return;
	utils::SetColor(Color4f{1,0,0,1});
	utils::FillRect(m_Center.x - m_Width / 2, m_Center.y - m_Height / 2, m_Width, m_Height);
}

void Bullet::Update(float elapsedSec, Enemy* pEnemies, int numEnemies)
{
	if (!m_IsActivated) return;
	m_Center.x += m_Velocity.x * elapsedSec;
	m_Center.y += m_Velocity.y * elapsedSec;
	bool isHit{ false };
	for (int i{ 0 }; i < numEnemies; ++i)
	{
		if (pEnemies[i].IsDead()) continue;
		isHit = pEnemies[i].DoHitTest(Rectf{ m_Center.x - m_Width / 2,m_Center.y - m_Height / 2 ,m_Width,m_Height });
		if (isHit) break;
	}
	m_IsActivated = !isHit;
}

void Bullet::Shoot(const Point2f& center, const Vector2f& velocity)
{
	if (m_IsActivated) return;
	m_IsActivated = true;
	m_Center = center;
	m_Velocity = velocity;
}

void Bullet::SetDimensions(float width, float height)
{
	m_Width = width;
	m_Height = height;
}

void Bullet::SetBoundaries(const Rectf& boundaries)
{
	m_Boundaries = boundaries;
}

void Bullet::CheckBoundaries()
{
	if (m_Center.y - m_Height > m_Boundaries.bottom + m_Boundaries.height)
	{
		m_IsActivated = false;
	}
}
