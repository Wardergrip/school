#include "pch.h"
#include "Mario.h"
#include "utils.h"
#include "level.h"
#include "Texture.h"
#include "Shell.h"
#include <iostream>
using namespace utils;

Mario::Mario()
	:GameObject()
	,m_pSmallMarioTexture{new Texture{"Resources/SmallMarioSheet.png"}}
	,m_pDeadGrowTexture{new Texture{"Resources/DeathAndGrow.png"}}
	,m_IsGrabbing{false}
	,m_LookUp{false}
	,m_Duck{false}
	,m_CurrentAnim{AnimState::neutral}
	,m_AnimTime{0}
	,m_FramesPerSec{10}
	,m_SpeedTreshHold{200}
	,m_MaxSpeed{500}
	,m_Position{20,300}
	,m_Velocity{0,0}
	,m_HorizontalDirection{1}
	,m_SprintAcceleration{150}
	,m_SprintDeceleration{450}
	,m_WalkSpeed{150}
	,m_SprintSpeed{400}
	,m_JumpSpeed{820}
	,m_IsInAir{false}
	,m_pShell{nullptr}
	,m_LoseShell{false}
	,m_IsFullyDead{false}
	,m_Stage{Stage::small}
{
	m_Rect = Rectf{0,(m_pSmallMarioTexture->GetHeight() / 3),m_pSmallMarioTexture->GetWidth() / 14,m_pSmallMarioTexture->GetHeight() / 3};
}

Mario::~Mario()
{
	delete m_pSmallMarioTexture;
	m_pSmallMarioTexture = nullptr;

	delete m_pDeadGrowTexture;
	m_pDeadGrowTexture = nullptr;

	if (m_pShell) delete m_pShell;
	m_pShell = nullptr;
}

void Mario::Draw() const
{	
	if (m_pShell)
	{
		glPushMatrix();
		{
			if (m_HorizontalDirection < 0) glTranslatef(m_pShell->GetRect().width - GetRect().width / 4 + 2*m_Position.x, 0, 0);
			glScalef(m_HorizontalDirection, 1, 1);
			m_pShell->Draw();
		}
		glPopMatrix();
	}
	glPushMatrix();
	{
		glTranslatef(m_Position.x, m_Position.y,0);
		if (m_HorizontalDirection > 0) glTranslatef(GetRect().width,0,0);
		glScalef(m_Scale * -m_HorizontalDirection, m_Scale, 0);
		if (!(m_Stage == Stage::dead)) m_pSmallMarioTexture->Draw(Point2f{ 0,0 }, m_Rect);
		else m_pDeadGrowTexture->Draw(Point2f{ 0,0 }, Rectf{ 0,0,m_Rect.width,m_Rect.height });
	}
	glPopMatrix();

	// // Debug: Shows collision
	// SetColor(Color4f{ 1,0,0,0.4f });
	// FillRect(GetRect());
}

void Mario::Update(float elapsedSec, Level& level)
{
	if (m_Stage == Stage::dead)
	{
		m_Velocity.y += m_Gravity.y * elapsedSec;
		m_Position.y += m_Velocity.y * elapsedSec;
		if (m_Position.y <= 0) m_IsFullyDead = true;
		return;
	}

	HitInfo HIv{}, HIh{};
	const bool onTop{ level.IsOnTop(GetRect(),HIv,m_Velocity) };
	const bool isHorTouch{ level.IsHorizontallyTouching(GetRect(),HIh,m_Velocity, m_HorizontalDirection) };
	const Uint8 *pStates = SDL_GetKeyboardState( nullptr );

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
				if (m_Velocity.x <= m_WalkSpeed) m_Velocity.x = m_WalkSpeed;
				if (m_Velocity.x <= m_SprintSpeed) m_Velocity.x += m_SprintAcceleration * elapsedSec;
			}
			else if (m_Velocity.x >= m_SpeedTreshHold) m_Velocity.x -= m_SprintDeceleration * elapsedSec;
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
				if (m_Velocity.x <= m_WalkSpeed) m_Velocity.x = m_WalkSpeed;
				if (m_Velocity.x <= m_SprintSpeed) m_Velocity.x += m_SprintAcceleration * elapsedSec;
			}
			else if (m_Velocity.x >= m_SpeedTreshHold) m_Velocity.x -= m_SprintDeceleration * elapsedSec;
			else m_Velocity.x = m_WalkSpeed;
		}
		else m_Velocity.x = 0;
		m_HorizontalDirection = -1;
	}
	else if (pStates[SDL_SCANCODE_LSHIFT])
	{
		if (isHorTouch && m_HorizontalDirection >= 0.5f)
		{
			m_Position.x -= (1 - HIh.lambda);
			m_Velocity.x = 0;
		}
		else if (isHorTouch && m_HorizontalDirection <= -0.5f)
		{
			m_Position.x += (1 - HIh.lambda);
			m_Velocity.x = 0;
		}
		else if (m_Velocity.x > 0) m_Velocity.x -= m_SprintDeceleration * elapsedSec;
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

	if (m_Position.y < -200) m_IsFullyDead = true;

	if (m_pShell)
	{
		m_pShell->SetPosition(Point2f{m_Position.x + 12,m_Position.y + 5});
		if (m_Duck) m_pShell->SetPosition(Point2f{ m_Position.x + 12,m_Position.y});

		if (!pStates[SDL_SCANCODE_LSHIFT])
		{
			m_LoseShell = true;
		}
	}
}

void Mario::UpdateAnim(float elapsedSec)
{
	float frameSpeedMultiplier{ std::abs(m_Velocity.x) / (m_MaxSpeed - 2 * m_WalkSpeed) };
	if (m_IsInAir && m_Velocity.y > 0)
	{
		m_CurrentAnim = AnimState::jump;
	}
	else if (m_IsInAir)
	{
		m_CurrentAnim = AnimState::fall;
	}
	else if (IsAtWalkingSpeed())
	{
		m_AnimTime += elapsedSec;
		if (m_AnimTime >= (1.0f / m_FramesPerSec))
		{
			m_AnimTime = 0;
			if (m_CurrentAnim == AnimState::neutral) m_CurrentAnim = AnimState::walk;
			else m_CurrentAnim = AnimState::neutral;
		}
	}
	else if (IsAtRunningSpeed())
	{
		m_AnimTime += elapsedSec;
		if (m_AnimTime >= (1.0f / (m_FramesPerSec * frameSpeedMultiplier)))
		{
			m_AnimTime = 0;
			if (m_CurrentAnim == AnimState::runNeutral) m_CurrentAnim = AnimState::run;
			else m_CurrentAnim = AnimState::runNeutral;
		}
	}
	else if (m_LookUp) m_CurrentAnim = AnimState::lookUp;
	else m_CurrentAnim = AnimState::neutral;
	if (m_Duck) m_CurrentAnim = AnimState::duck;

	if (m_IsGrabbing)
	{
		bool wasRunNeutral{ false };
		switch (m_CurrentAnim)
		{
		case Mario::AnimState::neutral:
			break;
		case::Mario::AnimState::runNeutral:
			m_CurrentAnim = AnimState::neutral;
			wasRunNeutral = true;
			break;
		case Mario::AnimState::lookUp:
			break;
		case Mario::AnimState::duck:
			break;
		case Mario::AnimState::walk:
			break;
		default:
			m_CurrentAnim = AnimState::walk;
			break;
		}
		// % 7 is safety measure
		m_Rect.left = (int(m_CurrentAnim) % 7) * m_Rect.width;
		m_Rect.bottom = 2 * (m_pSmallMarioTexture->GetHeight() / 3);
		if (wasRunNeutral) m_CurrentAnim = AnimState::runNeutral;
	}
	else
	{
		m_Rect.left = int(m_CurrentAnim) * m_Rect.width;
		m_Rect.bottom = (m_pSmallMarioTexture->GetHeight() / 3);
	}
}

void Mario::Jump()
{
	if (!m_IsInAir) m_Velocity.y = m_JumpSpeed;
}

void Mario::BounceJump()
{
	m_Velocity.y = m_JumpSpeed * 0.5f;
}

void Mario::Hurt()
{
	std::cout << "Ouch!\n";
	switch (m_Stage)
	{
	case Mario::Stage::dead:
		break;
	case Mario::Stage::small:
		m_Stage = Stage::dead;
		m_Velocity.x = 0;
		m_Velocity.y = 100;
		break;
	case Mario::Stage::big:
		m_Stage = Stage::small;
		break;
	case Mario::Stage::fire:
		m_Stage = Stage::big;
		break;
	}
}

void Mario::SetShell(Shell* pShell)
{
	m_pShell = pShell;
	m_IsGrabbing = true;
}

Shell* Mario::GiveShell()
{
	m_pShell->Throw(m_HorizontalDirection,m_Velocity);
	if (m_HorizontalDirection > 0.5f) m_pShell->SetPosition(Point2f{ m_Position.x + GetRect().width + 10,m_Position.y });
	else if (m_HorizontalDirection < -0.5f) m_pShell->SetPosition(Point2f{ m_Position.x - GetRect().width - 10,m_Position.y });

	Shell* pS{ m_pShell };
	m_pShell = nullptr;
	m_IsGrabbing = false;
	m_LoseShell = false;
	return pS;
}

Shell* Mario::GetShell() const
{
	return m_pShell;
}

float Mario::GetHorDirection() const
{
	return m_HorizontalDirection;
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

bool Mario::IsTryingToThrowShell() const
{
	return m_LoseShell;
}

Mario::Stage Mario::GetStage() const
{
	return m_Stage;
}

bool Mario::IsFullyDead() const
{
	return m_IsFullyDead;
}

void Mario::Grow()
{
	if (m_Stage == Stage::small) m_Stage = Stage::big;
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
