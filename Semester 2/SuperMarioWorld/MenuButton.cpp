#include "pch.h"
#include "MenuButton.h"
#include "Texture.h"
#include "utils.h"
using namespace utils;

MenuButton::MenuButton()
	:MenuButton(nullptr)
{
}

MenuButton::MenuButton(Texture* pTexture)
	:ButtonBase(pTexture)
	,m_IsActive{false}
	,m_ButtonColor{ 0.4f,0.4f,0.4f,1 }
{
	if (m_pTexture != nullptr)
	{
		AdjustRectToTexture();
	}
}

void MenuButton::SetActive(bool isActive)
{
	m_IsActive = isActive;
}

void MenuButton::SetButtonColor(const Color4f& buttonColor)
{
	m_ButtonColor = buttonColor;
}

void MenuButton::Draw() const
{
	SetColor(m_ButtonColor);
	if (m_IsActive) utils::FillRect(m_Button);
	m_pTexture->Draw(RectToBL());
}

bool MenuButton::IsActive() const
{
	return m_IsActive;
}