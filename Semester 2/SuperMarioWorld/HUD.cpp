#include "pch.h"
#include "HUD.h"

#include "Player.h"
#include "Texture.h"

const float HUD::m_Scale{ 2 };

HUD::HUD(const Player& player, const Window& window)
	:m_PlayerRef{player}
	,m_WindowRef{window}
	,m_pFont{}
	,m_pCourseClear{}
	,m_pPowerUpHold{}
	,m_pScoreTextures{}
{
	std::string root{ "Resources/HUD/" };
	m_pFont = new Texture{root + "Font.png"};
	m_pCourseClear = new Texture{root + "CourseClear.png"};
	m_pPowerUpHold = new Texture{root + "PowerUpHold.png"};
	m_pScoreTextures = new Texture{root + "ScoreTextures.png"};
}

HUD::~HUD()
{
	delete m_pFont;
	m_pFont = nullptr;
	delete m_pCourseClear;
	m_pCourseClear = nullptr;
	delete m_pPowerUpHold;
	m_pPowerUpHold = nullptr;
	delete m_pScoreTextures;
	m_pScoreTextures = nullptr;
}

void HUD::Draw() const
{
	Point2f marioInfoPoint{ 30,m_WindowRef.height - 20 - 32.f };
	Point2f holderPoint{ m_WindowRef.width / 2 - m_pPowerUpHold->GetWidth() / 8, m_WindowRef.height - m_pPowerUpHold->GetHeight() };
	DrawMario(marioInfoPoint);
	DrawX(Point2f{marioInfoPoint.x + 16.f, marioInfoPoint.y - 16.f});
	DrawLives(Point2f{marioInfoPoint.x + 40.f, marioInfoPoint.y - 16.f});
	DrawHolder(holderPoint);
}

void HUD::DrawMario(const Point2f& pos) const
{
	Rectf srcRect{8.f,8.f,64.f,8.f};
	glPushMatrix();
	{
		glTranslatef(pos.x, pos.y, 0);
		glScalef(m_Scale, m_Scale, 1);
		m_pFont->Draw(Point2f{}, srcRect);
	}
	glPopMatrix();
}

void HUD::DrawX(const Point2f& pos) const
{
	Rectf srcRect{40.f,8.f,8.f,8.f};
	glPushMatrix();
	{
		glTranslatef(pos.x, pos.y, 0);
		glScalef(m_Scale, m_Scale, 1);
		m_pScoreTextures->Draw(Point2f{}, srcRect);
	}
	glPopMatrix();
}

void HUD::DrawLives(const Point2f& pos) const
{
	Rectf srcRect{ (m_PlayerRef.GetLives() * 8.f),16.f,8.f,8.f};
	glPushMatrix();
	{
		glTranslatef(pos.x, pos.y, 0);
		glScalef(m_Scale, m_Scale, 1);
		m_pFont->Draw(Point2f{}, srcRect);
	}
	glPopMatrix();
}

void HUD::DrawHolder(const Point2f& pos) const
{
	glPushMatrix();
	{
		Rectf srcRect{ 0,0,m_pPowerUpHold->GetWidth() / 4,m_pPowerUpHold->GetHeight() / 3};
		glTranslatef(pos.x, pos.y, 0);
		glScalef(m_Scale, m_Scale, 1);
		m_pPowerUpHold->Draw(Point2f{},srcRect);
	}
	glPopMatrix();
}
