#pragma once
#include "ButtonBase.h"
class SettingsButton : public ButtonBase
{
public:
	SettingsButton(bool& setting, Texture* pTexture = nullptr);

	void Draw(float thickness = 2.0f) const;

private:
	bool& m_pSetting;
};

