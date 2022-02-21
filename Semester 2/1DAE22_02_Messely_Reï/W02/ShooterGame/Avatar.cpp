#include "pch.h"
#include "Avatar.h"
#include "Enemy.h"
#include "utils.h"

Avatar::Avatar(const Point2f& center, float width, float height)
	:m_Center{center}
	,m_Width{width}
	,m_Height{height}
	,m_Speed{100}
	,m_Boundaries{}
	,m_Bullet{10,20}
{
}

Avatar::Avatar()
	:Avatar(Point2f{},0,0)
{
}

void Avatar::Update(float elapsedSec, Enemy* pEnemies, int nrOfEnemies)
{
	HandleMoveKeysState(elapsedSec);
	m_Bullet.Update(elapsedSec, pEnemies, nrOfEnemies);
}

void Avatar::Draw() const
{
	utils::SetColor(Color4f{1,1,0,1});
	utils::DrawRect(m_Center.x - m_Width / 2, m_Center.y - m_Height / 2, m_Width, m_Height);
	m_Bullet.Draw();
}

void Avatar::SetCenter(const Point2f& center)
{
	m_Center = center;
}

void Avatar::SetDimensions(float width, float height)
{
	m_Width = width;
	m_Height = height;
}

void Avatar::SetBoundaries(const Rectf& boundaries)
{
	m_Boundaries = boundaries;
}

void Avatar::ProcessKeyDownEvent(const SDL_KeyboardEvent& e)
{
	switch (e.keysym.sym)
	{
	case SDLK_UP:
		m_Bullet.Shoot(m_Center, Vector2f{0, 300});
		break;
	}
}

void Avatar::Clamp()
{
	if (m_Center.x + m_Width / 2 > m_Boundaries.left + m_Boundaries.width) m_Center.x = m_Boundaries.left +m_Boundaries.width - m_Width / 2;
	else if (m_Center.x - m_Width / 2 < m_Boundaries.left) m_Center.x = m_Boundaries.left + m_Width / 2;
}

void Avatar::HandleMoveKeysState(float elapsedSec)
{
	const Uint8* pStates = SDL_GetKeyboardState(nullptr);
	if ( pStates[SDL_SCANCODE_RIGHT] )
	{
		m_Center.x += m_Speed * elapsedSec;
	}
	else if ( pStates[SDL_SCANCODE_LEFT])
	{
		m_Center.x -= m_Speed * elapsedSec;
	}
	Clamp();
}
