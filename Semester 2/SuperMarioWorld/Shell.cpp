#include "pch.h"
#include "Shell.h"
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
{
}

void Shell::Kick(float horizontalDirection)
{
	m_Velocity.x = horizontalDirection * m_KickSpeed;
}

void Shell::Update(float elapsedSec, Mario* pMario)
{
	if (IsOverlapping(pMario->GetRect(), this->GetRect()))
	{
		if (m_Velocity.x > 1 || m_Velocity.x < -1) pMario->Hurt();
		else Kick(pMario->GetHorDirection());
	}

	UpdateMovement(elapsedSec);
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
