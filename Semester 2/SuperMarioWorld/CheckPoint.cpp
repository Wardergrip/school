#include "pch.h"
#include "CheckPoint.h"
#include "Texture.h"
#include "Player.h"
#include "Mario.h"
#include "utils.h"
using namespace utils;

Texture* CheckPoint::m_pTexture{ nullptr };
int CheckPoint::m_Instances{ 0 };

CheckPoint::CheckPoint(const Point2f& pos)
	:GameObject{Rectf{0,0,0,0}}
	,m_IsTriggered{false}
	,m_Position{pos}
	,m_BarRect{Rectf{0,0,0,0}}
	,m_BarPos{pos}
	,m_VerticalVelocity{100.f}
{
	++m_Instances;
	if (m_Instances == 1) m_pTexture = new Texture{ "Resources/GoalAndCheckpoints.png" };
	m_Rect.width = 32.f;
	m_Rect.height = 64.f;

	m_BarRect.left = 32.f;
	m_BarRect.bottom = -61.f;
	m_BarRect.width = 19.f;
	m_BarRect.height = 3.f;
	m_BarPos = Point2f{ m_Position.x + 10.f,m_Position.y + m_Rect.height * 0.5f };
}

CheckPoint::~CheckPoint()
{
	--m_Instances;
	if (m_Instances == 0)
	{
		delete m_pTexture;
		m_pTexture = nullptr;
	}
}

void CheckPoint::Draw() const
{
	glPushMatrix();
	{
		// Frame
		glTranslatef(m_Position.x, m_Position.y, 0);
		glScalef(m_Scale, m_Scale, 1);
		m_pTexture->Draw(Point2f{}, m_Rect);
	}
	glPopMatrix();
	if (!m_IsTriggered)
	{
		glPushMatrix();
		{
			// Bar
			glTranslatef(m_BarPos.x, m_BarPos.y, 0);
			glScalef(m_Scale, m_Scale, 1);
			m_pTexture->Draw(Point2f{}, m_BarRect);
		}
		glPopMatrix();
	}
}

void CheckPoint::Update(float elapsedSec, Player* player)
{
	Rectf marioRect{ player->GetpMario()->GetRect()};
	if (IsOverlapping(marioRect, this->GetRect()))
	{
		m_IsTriggered = true;
		if (player->GetLastCheckPointPos().x > 4400.f) return;
		player->GetpMario()->Grow();
		player->SetLastCheckPointPos(GetPosition());
	}

	// Bar logic
	if (m_IsTriggered) return;
	Rectf posRect{ this->GetRect() };
	if (m_BarPos.y >= m_Position.y + posRect.height * 0.8f)
	{
		m_VerticalVelocity = -m_VerticalVelocity;
	}
	else if (m_BarPos.y <= m_Position.y + posRect.height * 0.2f)
	{
		m_VerticalVelocity = -m_VerticalVelocity;
	}
	m_BarPos.y += m_VerticalVelocity * elapsedSec;
}

Rectf CheckPoint::GetRect() const
{
	return Rectf(m_Position.x,m_Position.y,m_Rect.width*m_Scale,m_Rect.height*m_Scale);
}

Point2f CheckPoint::GetPosition() const
{
	return m_Position;
}
