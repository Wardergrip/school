#pragma once

#include "Vector2f.h"

class Texture;
class Unit;

class InfoPlate final
{
// STATICS
public:
	static void SetDrawInfoPlates(bool state);
	static void SwitchDrawInfoPlates();
	static bool IsDrawingInfoPlates();

private:
	static bool c_EnableDrawInfoplates;

// NON STATICS
public:
	InfoPlate(const Unit* trackingUnit, const Vector2f& offset);
	InfoPlate(const Unit* trackingUnit);
	InfoPlate(InfoPlate& infoplate) = delete;
	InfoPlate& operator=(InfoPlate& infoplate) = delete;
	InfoPlate(InfoPlate&& infoplate) = delete;
	InfoPlate& operator=(InfoPlate&& infoplate) = delete;
	~InfoPlate();

	void Draw() const;

	void SetName(const std::string& name);

private:
	const Unit* m_TrackingUnit;

	Rectf m_Plate;
	Vector2f m_Offset;
	Vector2f m_Scale;

	Rectf m_HealthBar;
	Color4f m_HealthBarColor;

	Texture* m_pName;
};

