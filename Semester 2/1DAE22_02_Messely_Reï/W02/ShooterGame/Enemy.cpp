#include "pch.h"
#include "Enemy.h"
#include "utils.h"

Enemy::Enemy(const Point2f& center, float width, float height)
	:m_Center(center)
	,m_Width(width)
	,m_Height(height)
	,m_IsDead(false)
{
}

Enemy::Enemy()
	:Enemy(Point2f{},0,0)
{
}

void Enemy::Draw() const
{
	if (m_IsDead) return;
	Color4f enemyColor{ 1,0,0,1 }; // Red
	utils::SetColor(enemyColor);
	utils::DrawRect(m_Center.x - m_Width / 2, m_Center.y - m_Height / 2, m_Width, m_Height, 2.0f);
}

bool Enemy::DoHitTest(const Rectf& other)
{
	if (utils::IsOverlapping(Rectf{ m_Center.x - m_Width / 2, m_Center.y - m_Height / 2, m_Width, m_Height }, other))
	{
		m_IsDead = true;
		return true;
	}
	return false;
}

void Enemy::SetCenter(const Point2f& center)
{
	m_Center = center;
}

void Enemy::SetDimensions(float width, float height)
{
	if (width >= 0) m_Width = width;
	if (height >= 0) m_Height = height;
}

bool Enemy::IsDead()
{
	return m_IsDead;
}
