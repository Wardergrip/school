#include "pch.h"
#include "Koopa.h"
#include "Shell.h"
#include "Texture.h"
#include "Level.h"
#include "Player.h"
#include "Mario.h"
#include "utils.h"
#include <iostream>
using namespace utils;

int Koopa::m_FramesPerSec{ 6 };

Koopa::Koopa(Color color, Type type)
	:KoopaBase(color,type)
	,m_pShell{nullptr}
	,m_IsDead{false}
	,m_IsHurt{false}
	,m_IsGivingShell{false}
	,m_AnimTime{0}
	,m_CurrentFrame{0}
{
	float walkSpeed{-50.f};
	m_Velocity.x = walkSpeed;
	if (type == Type::shelled) m_pShell = new Shell(color);
}

Koopa::~Koopa()
{
	delete m_pShell;
	m_pShell = nullptr;
}

void Koopa::Draw() const
{
	if (m_IsHurt && m_pShell)
	{
		m_pShell->Draw();
		return;
	}
	glPushMatrix();
	{
		glTranslatef(m_Position.x, m_Position.y, 0);
		glScalef(m_Scale, m_Scale, 1);
		if (m_Velocity.x > 1)
		{
			glScalef(-1, 1, 1);
			glTranslatef(-m_Rect.width, 0, 0);
		}
		m_pKoopaTexture->Draw(Point2f{}, m_Rect);
	}
	glPopMatrix();

	if (m_DrawHitBoxes) DrawHitboxes();
}

void Koopa::Update(float elapsedSec, Player* player)
{
	if (m_IsHurt && m_pShell)
	{
		m_pShell->Update(elapsedSec, player);
		if (m_pShell->GetYPos() < -300) m_IsDead = true;
		return;
	}
	Mario* pMario{ player->GetpMario() };

	if (IsOverlapping(pMario->GetRect(), GetTopHitbox()))
	{
		if (m_Type == Type::naked && m_IsHurt)
		{
			m_IsDead = true;
			player->AddScore(50);
		}
		else if (m_Type == Type::naked)
		{
			AboutToDie();
			pMario->BounceJump();
			m_Rect.left = -m_Rect.width; // Doesn't work?
			player->AddScore(50);
		}
		else if (m_Type == Type::shelled) m_IsGivingShell = true;
	}
	else if (IsOverlapping(pMario->GetRect(), GetSidesHitbox()))
	{
		if(!pMario->GetShell()) pMario->Hurt();
		else
		{
			AboutToDie();
			m_pShell->SetDeathStatus(true);
			pMario->GetShell()->SetDeathStatus(true);
			m_pLevelRef->Push_back(pMario->GiveShell());
		}
	}
	UpdateMovement(elapsedSec);
	UpdateAnim(elapsedSec);
}                                 

void Koopa::AboutToDie()
{
	if (!m_IsHurt)
	{
		if (m_pShell)
		{
			m_pShell->SetPosition(m_Position);
			m_pShell->SetDeathStatus(true);
		}
	}
	m_IsHurt = true;
}

void Koopa::ForceDie()
{
	m_IsDead = true;
}

Shell* Koopa::GiveShell()
{
	Shell* pS{ m_pShell };
	m_pShell->SetPosition(m_Position);
	m_pShell = nullptr;
	m_IsGivingShell = false;
	m_Type = Type::naked;
	m_Rect.left = 8 * m_Rect.width;
	m_Rect.height = 0.6f * m_Rect.height;
	this->SetPosition(Point2f{ m_Position.x - 50, m_Position.y });
	return pS;
}

void Koopa::SetShell(Shell* pShell)
{
	if (m_pShell != nullptr) throw "Trying to replace current shell\n";
	m_pShell = pShell;
	m_Type = Type::shelled;
	m_Rect.height = 27.f;
}

void Koopa::UpdateAnim(float elapsedSec)
{
	if (m_Velocity.x > 1 || m_Velocity.x < -1)
	{
		m_AnimTime += elapsedSec;
		if (m_AnimTime >= (1.0f / m_FramesPerSec))
		{
			m_AnimTime -= (1.0f / m_FramesPerSec);
			++m_CurrentFrame %= 2;
		}
	}
	else m_CurrentFrame = 0;
	
	switch (m_Type)
	{
	case KoopaBase::Type::shelled:
		m_Rect.left = m_CurrentFrame * m_Rect.width;
		break;
	case KoopaBase::Type::naked:
		m_Rect.left = 8 * m_Rect.width + m_CurrentFrame * m_Rect.width;
		break;
	}
}

bool Koopa::IsDead() const
{
	return m_IsDead;
}

bool Koopa::IsWantingToGiveShell() const
{
	return m_IsGivingShell;
}

Shell* Koopa::GetShell() const
{
	return m_pShell;
}
