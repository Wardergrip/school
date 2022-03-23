#include "pch.h"
#include "Shell.h"
#include "Player.h"
#include "Mario.h"
#include <iostream>
#include "utils.h"
using namespace utils;

int Shell::m_FramesPerSec{ 8 };
float Shell::m_KickSpeed{ 300 };

Shell::Shell(Color col)
	:KoopaBase(col,Type::shell)
	,m_AnimTime{0}
	,m_CurrentFrame{0}
	,m_Grab{false}
{
}

void Shell::Kick(float horizontalDirection)
{
	m_Velocity.x = horizontalDirection * m_KickSpeed;
}

void Shell::Throw(float horizontalDirection)
{
	m_Grab = false;
	Kick(horizontalDirection);
}

void Shell::Update(float elapsedSec, const Player& player)
{
	Mario* pMario{ player.GetpMario() };

	if (IsOverlapping(pMario->GetRect(), this->GetTopHitbox()))
	{
		if (m_Velocity.x < 0.5f && m_Velocity.x > -0.5f) Kick(pMario->GetHorDirection());
		else m_Velocity.x = 0;
		pMario->BounceJump();
	}
	else if (IsOverlapping(pMario->GetRect(), this->GetRect()))
	{
		if (m_Velocity.x > 1 || m_Velocity.x < -1)
		{
			if ((pMario->GetHorDirection() > 1 && m_Velocity.x > 1) || (pMario->GetHorDirection() < -1 && m_Velocity.x < -1))
			{
				pMario->Hurt();
			}
			else m_Grab = true;
		}
		else Kick(pMario->GetHorDirection());
	}

	UpdateMovement(elapsedSec);
	// Animation
	if (m_Velocity.x > 1 || m_Velocity.x < -1)
	{
		m_AnimTime += elapsedSec;
		if (m_AnimTime >= (1.0f / m_FramesPerSec))
		{
			m_AnimTime -= (1.0f / m_FramesPerSec);
			++m_CurrentFrame %= 4;
		}
	}
	m_Rect.left = 3 * m_Rect.width + m_CurrentFrame * m_Rect.width;
}

bool Shell::IsGrabbed() const
{
	return m_Grab;
}
