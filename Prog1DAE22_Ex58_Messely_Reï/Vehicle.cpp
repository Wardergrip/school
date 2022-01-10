#include "pch.h"
#include "Vehicle.h"

Vehicle::Vehicle(int id)
	:m_MaxSpeed{200}
	,m_MinSpeed{20}
	,m_IsActive{false}
	,m_Position{0,0}
{
		m_Speed = float((rand() % (m_MaxSpeed + 1 - m_MinSpeed) + m_MinSpeed));
		TextureFromFile("Resources/car-truck" + std::to_string(id + 1) + ".bmp", m_Texture);
}

void Vehicle::Reset()
{
	m_Position.x = -float((rand() % (300 + 1)));
	m_Speed = float((rand() % (m_MaxSpeed + 1 - m_MinSpeed) + m_MinSpeed));
	SetActive(true);
}

Vehicle::~Vehicle()
{
	DeleteTexture(m_Texture);
}

void Vehicle::Update(float elapsedSec, float windowWidth)
{
	if (m_IsActive)
	{
		m_Position.x += m_Speed * elapsedSec;
		if (m_Position.x >= windowWidth) m_Position.x = -m_Texture.width;
	}
}

void Vehicle::Draw()
{
	DrawTexture(m_Texture, m_Position);
}

bool Vehicle::IsIntersecting(const Point2f& pt)
{
	if ((pt.x > m_Position.x) && (pt.x < m_Position.x + m_Texture.width) && (pt.y > m_Position.y) && (pt.y < m_Position.y + m_Texture.height))
	{
		return true;
	}
	return false;
}

void Vehicle::SetActive(bool isActive)
{
	m_IsActive = isActive;
}

void Vehicle::SetYPos(float posY)
{
	m_Position.y = posY;
}
