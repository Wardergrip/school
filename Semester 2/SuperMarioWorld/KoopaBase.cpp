#include "pch.h"
#include "KoopaBase.h"
#include "Texture.h"
#include "Level.h"
#include "utils.h"
using namespace utils;
#include <iostream>

Texture* KoopaBase::m_pKoopaTexture{ nullptr };
unsigned int KoopaBase::m_Instances{ 0 };
Level* KoopaBase::m_pLevelRef{ nullptr };

void KoopaBase::InitLevelRef(Level* pLevelRef)
{
	m_pLevelRef = pLevelRef;
}

KoopaBase::KoopaBase(Color col, Type type)
	:GameObject(Rectf{0,0,0,0})
	,m_Color{col}
	,m_Type{type}
	,m_Position{}
	,m_Velocity{0,0}
{
	if (!m_pLevelRef) throw "[ERROR] Koopa's LevelRef is uninitialised!\n";
	++m_Instances;
	if (m_Instances == 1)
	{
		m_pKoopaTexture = new Texture("Resources/Koopa.png");
	}

	m_Rect.width = 16.f;
	m_Rect.height = 27.f;

	switch (m_Color)
	{
	case KoopaBase::Color::red:
		m_Rect.bottom = m_Rect.height;
		break;
	case KoopaBase::Color::green:
		m_Rect.bottom = 2 * m_Rect.height;
		break;
	case KoopaBase::Color::gray:
		m_Rect.bottom = 3 * m_Rect.height;
		break;
	}
	switch (m_Type)
	{
	case KoopaBase::Type::shell:
		m_Rect.left = 3 * m_Rect.width;
		m_Rect.height = 16.f;
		break;
	case KoopaBase::Type::shelled:
		m_Rect.left = 0;
		break;
	case KoopaBase::Type::naked:
		m_Rect.left = 8 * m_Rect.width;
		m_Rect.height = 16.f;
		break;
	}
}

KoopaBase::~KoopaBase()
{
	--m_Instances;
	if (m_Instances == 0)
	{
		delete m_pKoopaTexture;
		m_pKoopaTexture = nullptr;
	}
}

void KoopaBase::Draw() const
{
	glPushMatrix();
	{
		glTranslatef(m_Position.x, m_Position.y, 0);
		glScalef(m_Scale, m_Scale, 1);
		m_pKoopaTexture->Draw(Point2f{}, m_Rect);
	}
	glPopMatrix();
}

void KoopaBase::Update(float elapsedSec, const Player& player)
{
	UpdateMovement(elapsedSec);
}

void KoopaBase::UpdateMovement(float elapsedSec)
{
	HitInfo HIh{}, HIv{};
	const bool hitHorizontal{m_pLevelRef->IsHorizontallyTouching(GetRect(),HIh,m_Velocity,(m_Velocity.x)/(std::abs(m_Velocity.x)))};
	const bool isOnTop{ m_pLevelRef->IsOnTop(GetRect(),HIv,m_Velocity) };
	Rectf r{ m_Position.x,m_Position.y,m_Rect.width,m_Rect.height };
	if (isOnTop)
	{
		m_Velocity.y = 0;
		m_Position.y += (1 - HIv.lambda);
		if (m_Type != Type::shell && m_Color == Color::red)
		{
			if (!m_pLevelRef->IsFullyOnTop(GetRect(), m_Velocity)) m_Velocity.x = -m_Velocity.x;
		}
	}
	else m_Velocity += m_Gravity * elapsedSec;
	if (hitHorizontal)
	{
		m_Velocity.x = -m_Velocity.x;
	}

	m_Position += m_Velocity * elapsedSec;
}

void KoopaBase::SetPosition(const Point2f& pos)
{
	m_Position = pos;
}

void KoopaBase::SetVelocity(const Vector2f& vel)
{
	m_Velocity = vel;
}

Rectf KoopaBase::GetRect() const
{
	return Rectf{ m_Position.x,m_Position.y,m_Rect.width * m_Scale,m_Rect.height * m_Scale};
}

Rectf KoopaBase::GetTopHitbox() const
{
	Rectf r{ GetRect() };
	float horOffset{ 10 };
	return Rectf{m_Position.x + horOffset, m_Position.y + r.height *0.9f,r.width - 2 * horOffset,r.height * 0.2f};
}

Rectf KoopaBase::GetSidesHitbox() const
{
	Rectf r{ GetRect() };
	return Rectf{ m_Position.x - r.width * 0.1f,m_Position.y,r.width + r.width * 0.1f,r.height * 0.9f };
}
