#pragma once
#include "ButtonBase.h"
class SettingsButton final : public ButtonBase
{
public:
	SettingsButton(bool& setting, Texture* pTexture = nullptr);
	~SettingsButton();

	void Draw(float thickness = 2.0f) const;

private:
	const bool& m_pSetting;
	static Texture* m_pBoxTexture;
	static unsigned int m_Instances;
};

