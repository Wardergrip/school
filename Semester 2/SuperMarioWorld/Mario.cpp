#include "pch.h"
#include "Mario.h"
#include "utils.h"
#include "level.h"
#include <iostream>
using namespace utils;

Mario::Mario()
	:GameObject(Rectf{ 10,350,30,50 })
	,m_Velocity{0,0}
	,m_Gravity{0,-981}
	,m_LastHorDirection{0}
	,m_HorSpeed{150}
	,m_JumpSpeed{500}
	,m_IsInAir{false}
{
}

Mario::~Mario()
{
}

void Mario::Draw() const
{
	SetColor(Color4f{ 1,1,0,1 });
	FillRect(m_Rect);
}

void Mario::Update(float elapsedSec, Level& level)
{
	if (!level.IsOnTop(m_Rect))
	{
		m_Velocity += m_Gravity * elapsedSec;
		m_IsInAir = true;
	}
	else
	{
		m_Velocity.y = 0;
		m_IsInAir = false;
	}
	const Uint8 *pStates = SDL_GetKeyboardState( nullptr );
	if (pStates[SDL_SCANCODE_RIGHT])
	{
		if (level.IsHorizontallyTouching(m_Rect) && m_LastHorDirection <= -0.5f) m_Velocity.x = 0;
		else
		{
			m_Velocity.x = m_HorSpeed;
			m_LastHorDirection = -1;
		}
	}
	else if (pStates[SDL_SCANCODE_LEFT])
	{
		if (level.IsHorizontallyTouching(m_Rect) && m_LastHorDirection >= 0.5f) m_Velocity.x = 0;
		else
		{
			m_Velocity.x = -m_HorSpeed;
			m_LastHorDirection = 1;
		}
	}
	else m_Velocity.x = 0;
	if (pStates[SDL_SCANCODE_UP] && !m_IsInAir)
	{
		m_Velocity.y = m_JumpSpeed;
	}

	m_Rect.bottom += m_Velocity.y * elapsedSec;
	m_Rect.left += m_Velocity.x * elapsedSec;
}

Point2f Mario::GetPureLocation() const
{
	return Point2f(m_Rect.left,m_Rect.bottom);
}

Point2f Mario::GetMiddleBotLocation() const
{
	return Point2f(m_Rect.left + m_Rect.width / 2, m_Rect.bottom);
}

Rectf Mario::GetRect() const
{
	return m_Rect;
}
