#include "pch.h"
#include "Avatar.h"
#include "Level.h"
#include <iostream>
#include "Texture.h"
using namespace utils;

Avatar::Avatar()
	:m_pSpritesTexture{ new Texture{"Resources/Images/AvatarSheet.png"}}
	,m_ClipHeight{97.0f}
	,m_ClipWidth{72.0f}
	,m_NrOfFrames{10}
	,m_NrFramesPerSec{10}
	,m_AnimTime{0}
	,m_AnimFrame{0}
	,m_Position{50,280}
	,m_Shape{ 0, 0, 0, 0 }
	,m_HorSpeed{ 200.0f }
	,m_JumpSpeed{600.0f}
	,m_Velocity{0,0}
	,m_Acceleration{0,-981.0f}
	,m_ActionState{ActionState::moving}
	,m_AccuTransformSec{0}
	,m_MaxTransformSec{1.0f}
	,m_Power{0}
{
	m_Shape.bottom = m_pSpritesTexture->GetHeight();
	m_Shape.width = m_ClipWidth;
	m_Shape.height = m_ClipHeight;
}

Avatar::~Avatar()
{
	delete m_pSpritesTexture;
	m_pSpritesTexture = nullptr;
}

void Avatar::Draw() const
{
	/*switch (m_ActionState)
	{
	case Avatar::ActionState::waiting:
		SetColor(Color4f{ 1,1,0,1 });
		std::cout << "Waiting\n";
		break;
	case Avatar::ActionState::moving:
		SetColor(Color4f{ 1,0,0,1 });
		std::cout << "Moving\n";
		break;
	case Avatar::ActionState::transforming:
		std::cout << "Transforming\n";
		SetColor(Color4f{ 0,0.4f,1,1 });
		break;
	}*/
	glPushMatrix();
	{
		glTranslatef(m_Position.x,m_Position.y,0);
		if (m_Velocity.x < 0)
		{
			glScalef(-1, 1, 1);
			glTranslatef(-m_Shape.width, 0, 0);
		}
		m_pSpritesTexture->Draw(Point2f{ 0,0 }, m_Shape);
	}
	glPopMatrix();
	// Power
	/*for (int i{ 0 }; i < m_Power; ++i)
	{
		SetColor(Color4f{ 1,0,0,1 });
		float offset{ 5 };
		float side{ 5 };
		FillRect(m_Shape.left + offset, m_Shape.bottom + offset + i * offset + i * side, side, side);
	}*/
}

void Avatar::Update(float elapsedSec, const Level& level)
{
	if (m_ActionState == ActionState::transforming)
	{
		m_AccuTransformSec += elapsedSec;
		if (m_AccuTransformSec >= m_MaxTransformSec)
		{
			m_AccuTransformSec = 0;
			m_ActionState = ActionState::waiting;
			m_Velocity = Vector2f{0,0};
			++m_Power;
		}
		UpdateAnim(elapsedSec);
		return;
	}
	bool onGround{ level.IsOnGround(Rectf{m_Position.x,m_Position.y,m_Shape.width,m_Shape.height}) };
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
	m_Position.y += m_Velocity.y * elapsedSec;
	m_Position.x += m_Velocity.x;
	level.HandleCollision(m_Position, m_Shape, m_Velocity);

	UpdateAnim(elapsedSec);
}

void Avatar::PowerUpHit()
{
	m_ActionState = ActionState::transforming;
	//++m_Power;
}

Rectf Avatar::GetShape() const
{
	return Rectf{m_Position.x,m_Position.y,m_Shape.width,m_Shape.height};
}

void Avatar::UpdateAnim(float elapsedSec)
{
	m_AnimTime += elapsedSec;
	if (m_AnimTime >= 1.0f / m_NrFramesPerSec)
	{
		++m_AnimFrame %= m_NrOfFrames;
		m_AnimTime = 0;
	}
	m_Shape.left = (m_AnimFrame * m_Shape.width);
	m_Shape.bottom = m_Shape.height * (float(m_ActionState) + 1 + 3 * m_Power);
}
