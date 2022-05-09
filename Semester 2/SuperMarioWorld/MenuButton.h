#pragma once
#include "ButtonBase.h"
class MenuButton final : public ButtonBase
{
public:
	explicit MenuButton();
	explicit MenuButton(Texture* pTexture);
	MenuButton(const MenuButton& m) = delete;
	MenuButton& operator=(const MenuButton& m) = delete;
	MenuButton(MenuButton&& m) = delete;
	MenuButton& operator=(MenuButton&& m) = delete;
	~MenuButton() = default;

	void SetActive(bool isActive);

	void Draw() const;
	
	bool IsActive() const;

private:
	bool m_IsActive;
	const Color4f m_ButtonColor;
};

