#include "pch.h"
#include "Mario.h"
#include "utils.h"
#include "level.h"
#include "Texture.h"
#include <iostream>
using namespace utils;

Mario::Mario()
	:GameObject()
	,m_pTexture{new Texture{"Resources/SmallMarioSheet.png"}}
	,m_IsGrabbing{false}
	,m_AnimState{AnimState::neutral}
	,m_Position{20,300}
	,m_Velocity{0,0}
	,m_Gravity{0,-981}
	,m_LastHorDirection{-1}
	,m_HorSpeed{150}
	,m_JumpSpeed{500}
	,m_IsInAir{false}
{
	m_Rect = Rectf{0,1*(m_pTexture->GetHeight() / 3),m_pTexture->GetWidth() / 14,m_pTexture->GetHeight() / 3};
}

Mario::~Mario()
{
	delete m_pTexture;
	m_pTexture = nullptr;
}

void Mario::Draw() const
{

	/*SetColor(Color4f{ 1,1,0,1 });
	FillRect(GetRect());*/
	
	glPushMatrix();
	{
		glTranslatef(m_Position.x, m_Position.y,0);
		if (m_LastHorDirection < 0) glTranslatef(GetRect().width,0,0);
		glScalef(m_Scale * m_LastHorDirection, m_Scale, 0);
		m_pTexture->Draw(Point2f{0,0}, m_Rect);
	}
	glPopMatrix();
}

void Mario::Update(float elapsedSec, Level& level)
{
	HitInfo HI;
	if (!level.IsOnTop(GetRect(),HI) || m_Velocity.y > 0)
	{
		m_Velocity += m_Gravity * elapsedSec;
		m_IsInAir = true;
	}
	else
	{
		m_Position.y += (1 - HI.lambda);
		m_Velocity.y = 0;
		m_IsInAir = false;
	}
	const Uint8 *pStates = SDL_GetKeyboardState( nullptr );
	if (pStates[SDL_SCANCODE_RIGHT])
	{
		if (level.IsHorizontallyTouching(GetRect()) && m_LastHorDirection <= -0.5f) m_Velocity.x = 0;
		else
		{
			m_Velocity.x = m_HorSpeed;
			m_LastHorDirection = -1;
		}
	}
	else if (pStates[SDL_SCANCODE_LEFT])
	{
		if (level.IsHorizontallyTouching(GetRect()) && m_LastHorDirection >= 0.5f) m_Velocity.x = 0;
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

	m_Position += m_Velocity * elapsedSec;
	UpdateAnim(elapsedSec);
}

void Mario::UpdateAnim(float elapsedSec)
{
	if (m_IsInAir && m_Velocity.y > 0)
	{
		m_AnimState = AnimState::jump;
	}
	else if (m_IsInAir)
	{
		m_AnimState = AnimState::fall;
	}
	else if (m_Velocity.x > 0)
	{
		m_AnimState = AnimState::walk;
	}
	else m_AnimState = AnimState::neutral;

	m_Rect.left = int(m_AnimState) * m_Rect.width;
}

Point2f Mario::GetPureLocation() const
{
	return m_Position;
}

Point2f Mario::GetMiddleBotLocation() const
{
	return Point2f(m_Position.x + m_Rect.width / 2, m_Position.y);
}

Rectf Mario::GetRect() const
{
	return Rectf{m_Position.x,m_Position.y,m_Scale * m_Rect.width,m_Scale * m_Rect.height};
}
