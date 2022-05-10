#include "pch.h"
#include "Shell.h"
#include "Player.h"
#include "Mario.h"
#include <iostream>
#include "utils.h"
#include "Texture.h"
using namespace utils;

int Shell::m_FramesPerSec{ 8 };
float Shell::m_KickSpeed{ 300 };

Shell::Shell(Color col)
	:KoopaBase(col,Type::shell)
	,m_AnimTime{0}
	,m_CurrentFrame{0}
	,m_Grab{false}
	,m_IsDead{false}
	,m_GoIn{false}
	,m_MarioUp{false}
{
}

void Shell::Kick(float horizontalDirection)
{
	if (!m_MarioUp) m_Velocity.x = horizontalDirection * m_KickSpeed;
	else
	{
		m_Velocity.y = m_KickSpeed*4;
	}
}

void Shell::Throw(float horizontalDirection, const Vector2f& velocity)
{
	float amplifier{ 1.5f };
	m_Grab = false;
	Kick(horizontalDirection);
	if (horizontalDirection > 0.5f)
	{
		if (m_Velocity.x < (velocity.x * amplifier))
		{
			m_Velocity.x = velocity.x * amplifier;
		}
	}
	else if (horizontalDirection < -0.5f)
	{
		if (m_Velocity.x > (-velocity.x * amplifier))
		{
			m_Velocity.x = -velocity.x * amplifier;
		}
	}
	m_MarioUp = false;
}

void Shell::Draw() const
{
	glPushMatrix();
	{
		glTranslatef(m_Position.x, m_Position.y, 0);
		glScalef(m_Scale, m_Scale, 1);
		if (m_IsDead)
		{
			glScalef(1, -1, 1);
		}
		m_pKoopaTexture->Draw(Point2f{}, m_Rect);
	}
	glPopMatrix();

	if (m_DrawHitBoxes) DrawHitboxes();
}

void Shell::Update(float elapsedSec, Player& player)
{
	if (m_IsDead)
	{
		m_Velocity += m_Gravity * elapsedSec;
		m_Position += m_Velocity * elapsedSec;
		return;
	}
	const Uint8* pStates = SDL_GetKeyboardState(nullptr);
	Mario* pMario{ player.GetpMario() };

	if (IsOverlapping(pMario->GetRect(), this->GetTopHitbox()))
	{
		if (m_Velocity.x < 0.5f && m_Velocity.x > -0.5f) Kick(pMario->GetHorDirection());
		else m_Velocity.x = 0;
		pMario->BounceJump();
	}
	else if (IsOverlapping(pMario->GetRect(), this->GetSidesHitbox()))
	{
		if (m_Velocity.x > 1 || m_Velocity.x < -1)
		{
			if (((pMario->GetHorDirection() > 0.5f) && (m_Velocity.x < -1)) || ((pMario->GetHorDirection() < -0.5f) && (m_Velocity.x > 1)))
			{
				pMario->Hurt();
			}
			else if (pStates[SDL_SCANCODE_LSHIFT])
			{
				m_Grab = true;
				m_AnimTime = 0;
				m_CurrentFrame = 0;
			}
			else pMario->Hurt();
		}
		else if (pStates[SDL_SCANCODE_LSHIFT])
		{
			m_Grab = true;
			m_AnimTime = 0;
			m_CurrentFrame = 0;
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

int Shell::UpdateShellKoopaCollisions(std::vector<Koopa*>& pKs)
{
	for (size_t i{0}; i < pKs.size(); ++i)
	{
		if (pKs[i] == nullptr) continue;
		if (IsOverlapping(pKs[i]->GetRect(), this->GetRect()))
		{
			if (m_Velocity.x > 1 || m_Velocity.x < -1)
			{
				if (pKs[i]->GetType() == Type::naked)
				{
					pKs[i]->ForceDie();
				}
				else
				{
					pKs[i]->AboutToDie();
				}
			}
			else if (!pKs[i]->GetShell())
			{
				m_GoIn = true;
				return int(i);
			}
		}
	}
	return -1;
}

void Shell::UpdateShellCollisions(std::vector<Shell*>& pSs)
{
	for (size_t i{ 0 }; i < pSs.size(); ++i)
	{
		if (pSs[i] == nullptr) continue;
		else if (pSs[i] == this) continue;
		if (IsOverlapping(pSs[i]->GetRect(), GetRect()))
		{
			if (m_Velocity.x > 1 || m_Velocity.x < -1)
			{
				pSs[i]->m_IsDead = true;
				std::cout << "Shell x shell hit\n";
			}
			else m_IsDead = true;
		}
	}
}

void Shell::SetGrabbed(bool grabbed)
{
	m_Grab = grabbed;
}

void Shell::SetUpStatus(bool status)
{
	m_MarioUp = status;
}

bool Shell::IsGrabbed() const
{
	return m_Grab;
}

bool Shell::IsGoingIn() const
{
	return m_GoIn;
}

float Shell::GetYPos() const
{
	return m_Position.y;
}

void Shell::SetDeathStatus(bool status)
{
	m_IsDead = status;
	if (m_IsDead) m_Velocity.y = 400;
}
