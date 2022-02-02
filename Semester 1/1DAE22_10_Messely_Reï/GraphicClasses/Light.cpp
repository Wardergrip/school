#include "pch.h"
#include "Light.h"
using namespace utils;

Light::Light(const Rectf& rect, const Color4f& color)
	:m_Rect{rect}
	,m_IsOn{ false }
	,m_Color{color}	
{
}
Light::~Light()
{
}

void Light::Draw()
{
	if (m_IsOn)
	{
		SetColor(m_Color);
	}
	else 
	{
		SetColor(0.5f, 0.5f, 0.5f, m_Color.a);
	}
	FillRect(m_Rect);
	SetColor(1, 1, 1, 1);
	DrawRect(m_Rect);
}

bool Light::IsHit(const Point2f& pos)
{
	if (IsInsideRect(m_Rect, pos))
	{
		m_IsOn = !m_IsOn;
		return true;
	}
	return false;
}

bool Light::IsOn()
{
	return m_IsOn;
}
