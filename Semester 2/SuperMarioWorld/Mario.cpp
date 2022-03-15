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
	,m_LookUp{false}
	,m_Duck{false}
	,m_AnimState{AnimState::neutral}
	,m_AnimTime{0}
	,m_FramesPerSec{10}
	,m_SpeedTreshHold{200}
	,m_MaxSpeed{500}
	,m_Position{20,300}
	,m_Velocity{0,0}
	,m_SprintAcceleration{100}
	,m_HorizontalDirection{1}
	,m_WalkSpeed{150}
	,m_SprintSpeed{400}
	,m_JumpSpeed{700}
	,m_IsInAir{false}
{
	m_Rect = Rectf{0,(m_pTexture->GetHeight() / 3),m_pTexture->GetWidth() / 14,m_pTexture->GetHeight() / 3};
}

Mario::~Mario()
{
	delete m_pTexture;
	m_pTexture = nullptr;
}

void Mario::Draw() const
{	
	glPushMatrix();
	{
		glTranslatef(m_Position.x, m_Position.y,0);
		if (m_HorizontalDirection > 0) glTranslatef(GetRect().width,0,0);
		glScalef(m_Scale * -m_HorizontalDirection, m_Scale, 0);
		m_pTexture->Draw(Point2f{0,0}, m_Rect);
	}
	glPopMatrix();

	// // Debug: Shows collision
	// SetColor(Color4f{ 1,0,0,0.4f });
	// FillRect(GetRect());
}

void Mario::Update(float elapsedSec, Level& level)
{
	HitInfo HIv{}, HIh{};
	const bool onTop{ level.IsOnTop(GetRect(),HIv,m_Velocity) };
	const bool isHorTouch{ level.IsHorizontallyTouching(GetRect(),HIh,m_Velocity) };
	if (!onTop || m_Velocity.y > 0)
	{
		m_Velocity += m_Gravity * elapsedSec;
		m_IsInAir = true;
	}
	else
	{
		m_Position.y += (1 - HIv.lambda);
		m_Velocity.y = 0;
		m_IsInAir = false;
	}
	const Uint8 *pStates = SDL_GetKeyboardState( nullptr );
	// Trying to move right
	if (pStates[SDL_SCANCODE_RIGHT])
	{
		if (isHorTouch && m_HorizontalDirection >= 0.5f)
		{
			m_Position.x -= (1 - HIh.lambda);
			m_Velocity.x = 0;
		}
		else if (!m_Duck || m_IsInAir)
		{
			if (pStates[SDL_SCANCODE_LSHIFT])
			{
				if (m_Velocity.x < m_WalkSpeed) m_Velocity.x = m_WalkSpeed;
				if (m_Velocity.x < m_SprintSpeed) m_Velocity.x += m_SprintAcceleration * elapsedSec;
			}
			else if (m_Velocity.x > m_SpeedTreshHold) m_Velocity.x -= m_SprintAcceleration * elapsedSec;
			else m_Velocity.x = m_WalkSpeed;
		}
		else m_Velocity.x = 0;
		m_HorizontalDirection = 1;
	}
	// Trying to move left
	else if (pStates[SDL_SCANCODE_LEFT])
	{
		if (isHorTouch && m_HorizontalDirection <= -0.5f)
		{
			m_Position.x += (1 - HIh.lambda);
			m_Velocity.x = 0;
		}
		else if (!m_Duck || m_IsInAir)
		{
			if (pStates[SDL_SCANCODE_LSHIFT])
			{
				if (m_Velocity.x < m_WalkSpeed) m_Velocity.x = m_WalkSpeed;
				if (m_Velocity.x < m_SprintSpeed) m_Velocity.x += m_SprintAcceleration * elapsedSec;
			}
			else if (m_Velocity.x > m_SpeedTreshHold) m_Velocity.x -= m_SprintAcceleration * elapsedSec;
			else m_Velocity.x = m_WalkSpeed;
		}
		else m_Velocity.x = 0;
		m_HorizontalDirection = -1;
	}
	else m_Velocity.x = 0;

	// Trying to look up
	if (pStates[SDL_SCANCODE_UP]) m_LookUp = true;
	else m_LookUp = false;
	// Trying to duck
	if (pStates[SDL_SCANCODE_DOWN]) m_Duck = true;
	else m_Duck = false;

	m_Position.x += m_HorizontalDirection * m_Velocity.x * elapsedSec;
	m_Position.y += m_Velocity.y * elapsedSec;
	UpdateAnim(elapsedSec);
}

void Mario::UpdateAnim(float elapsedSec)
{
	float frameSpeedMultiplier{ std::abs(m_Velocity.x) / (m_MaxSpeed - 2 * m_WalkSpeed) };
	if (m_IsInAir && m_Velocity.y > 0)
	{
		m_AnimState = AnimState::jump;
	}
	else if (m_IsInAir)
	{
		m_AnimState = AnimState::fall;
	}
	else if (IsAtWalkingSpeed())
	{
		m_AnimTime += elapsedSec;
		if (m_AnimTime >= (1.0f / m_FramesPerSec))
		{
			m_AnimTime = 0;
			if (m_AnimState == AnimState::neutral) m_AnimState = AnimState::walk;
			else m_AnimState = AnimState::neutral;
		}
	}
	else if (IsAtRunningSpeed())
	{
		m_AnimTime += elapsedSec;
		if (m_AnimTime >= (1.0f / (m_FramesPerSec * frameSpeedMultiplier)))
		{
			m_AnimTime = 0;
			if (m_AnimState == AnimState::runNeutral) m_AnimState = AnimState::run;
			else m_AnimState = AnimState::runNeutral;
		}
	}
	else if (m_LookUp) m_AnimState = AnimState::lookUp;
	else m_AnimState = AnimState::neutral;
	if (m_Duck) m_AnimState = AnimState::duck;

	if (m_IsGrabbing)
	{
		switch (m_AnimState)
		{
		case Mario::AnimState::neutral:
		case Mario::AnimState::lookUp:
		case Mario::AnimState::duck:
		case Mario::AnimState::walk:
			break;
		default:
			m_AnimState = AnimState::walk;
			break;
		}
		// % 7 is safety measure
		m_Rect.left = (int(m_AnimState) % 7) * m_Rect.width;
		m_Rect.bottom = 2 * (m_pTexture->GetHeight() / 3);
	}
	else
	{
		m_Rect.left = int(m_AnimState) * m_Rect.width;
		m_Rect.bottom = (m_pTexture->GetHeight() / 3);
	}
}

void Mario::Jump()
{
	if (!m_IsInAir) m_Velocity.y = m_JumpSpeed;
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
	Rectf r{ m_Position.x,m_Position.y,m_Scale * m_Rect.width,m_Scale * m_Rect.height };
	if (!m_Duck) return r;
	return Rectf{r.left,r.bottom,r.width,r.height * 0.55f};
}

void Mario::Grow()
{
}

bool Mario::IsAtWalkingSpeed()
{
	if (m_Velocity.x > m_SpeedTreshHold) return false;
	if (m_Velocity.x < 1) return false;
	return true;
}

bool Mario::IsAtRunningSpeed()
{
	if (m_Velocity.x > m_SpeedTreshHold) return true;
	return false;
}
