#include "pch.h"
#include "SettingsButton.h"
#include "Texture.h"
#include "utils.h"
#include "MenuButton.h"
using namespace utils;

SettingsButton::SettingsButton(bool& setting, Texture* pTexture)
	:ButtonBase{pTexture}
	,m_pSetting{setting}
{
	SetRect(Rectf{ 0,0,40,40 });
}

void SettingsButton::Draw(float thickness) const
{
	SetColor(Color4f{1,1,1,1});
	DrawRect(m_Button, thickness);
	if (m_pSetting) FillEllipse(CenterOf(),m_Button.width/2,m_Button.height/2);
	m_pTexture->Draw(Point2f{ RectToBL().x - m_pTexture->GetWidth() / 3, RectToBL().y + m_pTexture->GetHeight() * 1.5f });
}