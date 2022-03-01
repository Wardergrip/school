#include "pch.h"
#include "Avatar.h"
#include "Level.h"
#include <iostream>
using namespace utils;

Avatar::Avatar()
	:m_Shape{ 50, 280, 36, 97 }
	,m_HorSpeed{ 200.0f }
	,m_JumpSpeed{600.0f}
	,m_Velocity{0,0}
	,m_Acceleration{0,-981.0f}
	,m_ActionState{ActionState::moving}
	,m_AccuTransformSec{0}
	,m_MaxTransformSec{1.0f}
	,m_Power{0}
{
}

void Avatar::Draw() const
{
	switch (m_ActionState)
	{
	case Avatar::ActionState::waiting:
		SetColor(Color4f{ 1,1,0,1 });
		break;
	case Avatar::ActionState::moving:
		SetColor(Color4f{ 1,0,0,1 });
		break;
	case Avatar::ActionState::transforming:
		SetColor(Color4f{ 0,0.4f,1,1 });
		break;
	}
	FillRect(m_Shape);
	for (int i{ 0 }; i < m_Power; ++i)
	{
		SetColor(Color4f{ 0,0,0,1 });
		float offset{ 5 };
		float side{ 5 };
		FillRect(m_Shape.left + offset, m_Shape.bottom + offset + i * offset + i * side, side, side);
	}
}

void Avatar::Update(float elapsedSec, const Level& level)
{
	bool onGround{ level.IsOnGround(m_Shape) };
	if (m_ActionState == ActionState::transforming)
	{
		m_AccuTransformSec += elapsedSec;
		if (m_AccuTransformSec >= m_MaxTransformSec)
		{
			m_AccuTransformSec = 0;
			m_ActionState = ActionState::waiting;
			m_Velocity = Vector2f{0,0};
		}
		return;
	}
	if (onGround)
	{
		m_Velocity = Vector2f{ 0,0 };
		m_ActionState = ActionState::waiting;
		const Uint8* pStates = SDL_GetKeyboardState(nullptr);
		if (pStates[SDL_SCANCODE_RIGHT])
		{
			m_ActionState = ActionState::moving;
			m_Velocity.x = m_HorSpeed * elapsedSec;
		}
		if (pStates[SDL_SCANCODE_LEFT])
		{
			m_ActionState = ActionState::moving;
			m_Velocity.x = -m_HorSpeed * elapsedSec;
		}
		if (pStates[SDL_SCANCODE_UP])
		{
			m_ActionState = ActionState::moving;
			m_Velocity.y = m_JumpSpeed;
		}
	}
	else
	{
		m_Velocity += m_Acceleration * elapsedSec;
	}
	m_Shape.left += m_Velocity.x;
	m_Shape.bottom += m_Velocity.y * elapsedSec;
}

void Avatar::PowerUpHit()
{
	m_ActionState = ActionState::transforming;
	++m_Power;
}

Rectf Avatar::GetShape() const
{
	return m_Shape;
}
