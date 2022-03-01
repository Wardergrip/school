#pragma once
#include "ButtonBase.h"
class MenuButton : public ButtonBase
{
public:
	MenuButton();
	MenuButton(Texture* pTexture);

	void SetActive(bool isActive);
	void SetButtonColor(const Color4f& buttonColor);

	void Draw() const;
	
	bool IsActive() const;

private:
	bool m_IsActive;
	Color4f m_ButtonColor;
};

