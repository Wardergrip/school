#include "pch.h"
#include "SettingsButton.h"
#include "Texture.h"
#include "utils.h"
#include "MenuButton.h"
#include <iostream>
using namespace utils;

unsigned int SettingsButton::m_Instances{ 0 };
Texture* SettingsButton::m_pBoxTexture{ nullptr };

SettingsButton::SettingsButton(bool& setting, Texture* pTexture)
	:ButtonBase{pTexture}
	,m_pSetting{setting}
{
	SetRect(Rectf{ 0,0,50,50 });
	++m_Instances;
	if (m_Instances == 1) m_pBoxTexture = new Texture{ "Resources/SettingsButton.png" };
}

SettingsButton::~SettingsButton()
{
	delete m_pBoxTexture;
	m_pBoxTexture = nullptr;
	--m_Instances;
	if (m_Instances == 0)
	{
		delete m_pBoxTexture;
		m_pBoxTexture = nullptr;
	}
}

void SettingsButton::Draw(float thickness) const
{
	Vector2f scalingFactor{m_Button.width / (m_pBoxTexture->GetWidth() / 2), m_Button.height / m_pBoxTexture->GetHeight()};
	SetColor(Color4f{1,1,1,1});
	glPushMatrix();
	{
		glTranslatef(m_Button.left,m_Button.bottom,0);
		glScalef(scalingFactor.x, scalingFactor.y, 0);
		m_pBoxTexture->Draw(Point2f{0,0}, Rectf{int(m_pSetting) * m_pBoxTexture->GetWidth() / 2, m_pBoxTexture->GetHeight(), m_pBoxTexture->GetWidth() / 2, m_pBoxTexture->GetHeight()});
	}
	glPopMatrix();
	m_pTexture->Draw(Point2f{ RectToBL().x - m_pTexture->GetWidth() / 3, RectToBL().y + m_pTexture->GetHeight() * 1.5f });
}