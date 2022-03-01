#include "pch.h"
#include "SettingsButton.h"
#include "Texture.h"
#include "utils.h"
#include "MenuButton.h"
using namespace utils;

unsigned int SettingsButton::m_Instances{ 0 };
Texture* SettingsButton::m_pBoxTexture{ nullptr };

SettingsButton::SettingsButton(bool& setting, Texture* pTexture)
	:ButtonBase{pTexture}
	,m_pSetting{setting}
{
	SetRect(Rectf{ 0,0,40,40 });
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
	SetColor(Color4f{1,1,1,1});
	m_pBoxTexture->Draw(m_Button, Rectf{m_Button.left + int(m_pSetting) * m_Button.width, m_Button.bottom, m_Button.width, m_Button.height});
	m_pTexture->Draw(Point2f{ RectToBL().x - m_pTexture->GetWidth() / 3, RectToBL().y + m_pTexture->GetHeight() * 1.5f });
}