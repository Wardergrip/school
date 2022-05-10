#include "pch.h"
#include "MysteryBox.h"
#include "Texture.h"
#include "utils.h"
using namespace utils;
#include "PickUp.h"

int MysteryBox::m_Instances{ 0 };
Texture* MysteryBox::m_pTexture{ nullptr };
const int MysteryBox::m_FramesPerSec{ 6 };

MysteryBox::MysteryBox(const Point2f& pos, PickUp* pPickUp)
	:m_pPickUp{pPickUp}
	,m_AccuSec{0}
	,m_CurrentFrame{0}
	,m_Position{pos}
	,m_WantsToGive{false}
	,m_IsBumped{false}
	,m_BumpedAccuSec{0}
	,m_PrebumpedYPos{pos.y}
{
	++m_Instances;
	if (m_Instances == 1)
	{
		m_pTexture = new Texture{"Resources/MysteryBox.png"};
	}
	m_Rect = Rectf{ 0,0,m_pTexture->GetWidth() / 5,m_pTexture->GetHeight()};
}

MysteryBox::~MysteryBox()
{
	--m_Instances;
	if (m_Instances == 0)
	{
		delete m_pTexture;
		m_pTexture = nullptr;
	}
	delete m_pPickUp;
	m_pPickUp = nullptr;
}

void MysteryBox::Draw() const
{
	glPushMatrix();
	{
		glTranslatef(m_Position.x, m_Position.y, 0);
		glScalef(m_Scale, m_Scale, 1);
		m_pTexture->Draw(Point2f{}, m_Rect);
	}
	glPopMatrix();
	if (m_pPickUp && m_IsBumped) m_pPickUp->Draw();
}

void MysteryBox::Update(float elapsedSec)
{
	if (m_pPickUp) UpdateAnim(elapsedSec);

	if (m_IsBumped)
	{
		m_BumpedAccuSec += elapsedSec;
		m_Position.y = m_PrebumpedYPos - 2500.f*(m_BumpedAccuSec * m_BumpedAccuSec) + 600.f * m_BumpedAccuSec;
		if (m_Position.y <= m_PrebumpedYPos)
		{
			m_IsBumped = false;
			m_Position.y = m_PrebumpedYPos;
			m_WantsToGive = true;
		}
		if (m_pPickUp)
		{
			switch (m_pPickUp->GetType())
			{
			case PickUp::Type::coin:
				m_pPickUp->SetPosition(Point2f{ m_Position.x,m_Position.y + GetRect().height + m_BumpedAccuSec * 200.f });
				break;
			default:
				m_pPickUp->SetPosition(Point2f{ m_Position.x,m_Position.y + GetRect().height + 4 });
				break;
			}
		}
	}
}

Rectf MysteryBox::GetRect() const
{
	return Rectf(m_Position.x,m_Position.y,m_Rect.width * m_Scale,m_Rect.height * m_Scale);
}

Rectf MysteryBox::GetBottomHitbox() const
{
	Rectf r{ GetRect() };
	float horOffset{ 1 };
	return Rectf{ m_Position.x + horOffset, m_Position.y - r.height * 0.2f,r.width - 2* horOffset,r.height * 0.2f };
}

bool MysteryBox::IsWantingToGivePickUp() const
{
	if (m_pPickUp == nullptr)
	{
		return false;
	}
	return m_WantsToGive;
}

bool MysteryBox::IsOverlapping(const Rectf& other) const
{
	return utils::IsOverlapping(other,GetRect());
}

bool MysteryBox::IsOverlappingBottomHitbox(const Rectf& other) const
{
	return utils::IsOverlapping(GetBottomHitbox(),other);
}

PickUp* MysteryBox::GivePickUp()
{
	PickUp* p{ m_pPickUp };
	m_pPickUp->SetPosition(Point2f{ m_Position.x,m_Position.y + GetRect().height + 4 });
	m_pPickUp = nullptr;
	m_IsBumped = false;
	m_WantsToGive = false;
	m_Rect.left = 0;
	return p;
}

PickUp* MysteryBox::GetPickUp() const
{
	return m_pPickUp;
}

void MysteryBox::Bump()
{
	if (m_pPickUp) m_IsBumped = true;
}

void MysteryBox::UpdateAnim(float elapsedSec)
{
	m_AccuSec += elapsedSec;
	if (m_AccuSec >= (1.0f / m_FramesPerSec))
	{
		m_AccuSec -= (1.0f / m_FramesPerSec);
		++m_CurrentFrame %= 4;
		m_Rect.left = (m_CurrentFrame + 1)  * m_Rect.width;
	}
}
