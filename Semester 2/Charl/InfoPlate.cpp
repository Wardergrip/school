#include "pch.h"
#include "InfoPlate.h"

#include "Texture.h"

#include "utils.h"
using namespace utils;

#include "unit.h"

// STATICS
bool InfoPlate::c_EnableDrawInfoplates{ true };

void InfoPlate::SetDrawInfoPlates(bool state)
{
	c_EnableDrawInfoplates = state;
}

void InfoPlate::SwitchDrawInfoPlates()
{
	c_EnableDrawInfoplates = !c_EnableDrawInfoplates;
}

bool InfoPlate::IsDrawingInfoPlates()
{
	return c_EnableDrawInfoplates;
}

// NON STATICS
InfoPlate::InfoPlate(const Unit* trackingUnit, const Vector2f& offset)
	:UserInterfaceElement(Rectf{ 0,0,150,40 })
	,m_TrackingUnit{trackingUnit}
	,m_Offset{offset}
	,m_Scale{1,1}
	,m_HealthBar{0,0,130,10}
	,m_HealthBarColor{ Color4f{1,0,0,1} }
	,m_pName{}
{
	m_Rect.left = -m_Rect.width / 2;
	m_Rect.bottom = -m_Rect.height / 2;

	m_HealthBar.left = -m_HealthBar.width / 2;
	m_HealthBar.bottom = -m_HealthBar.height / 2;
}

InfoPlate::InfoPlate(const Unit* trackingUnit)
	:InfoPlate(trackingUnit,Vector2f{0,45})
{
}

InfoPlate::~InfoPlate()
{
	delete m_pName;
	m_pName = nullptr;
}

void InfoPlate::Draw() const
{
	if (!c_EnableDrawInfoplates)
	{
		return;
	}

	Point2f trackingPoint{ m_TrackingUnit->GetTransform().location };
	glPushMatrix();
	{
		glTranslatef(trackingPoint.x, trackingPoint.y, 0);
		glTranslatef(m_Offset.x, m_Offset.y, 0);
		
		// InfoPlate base plate
		glScalef(m_Scale.x, m_Scale.y, 1);
		SetColor(Color4f{ 0.5f,0.5f,0.5f,1 });
		FillRect(m_Rect);
		
		// Healthbar and line around it
		glTranslatef(0, -10, 0);
		SetColor(m_HealthBarColor);
		FillRect(Rectf{m_HealthBar.left,m_HealthBar.bottom,m_HealthBar.width * m_TrackingUnit->GetBasicStats().GetPercentageHealth(),m_HealthBar.height});
		SetColor(Color4f{ 0,0,0,1 });
		DrawRect(m_HealthBar, 2);

		if (m_pName)
		{
			m_pName->Draw(Point2f{ -m_pName->GetWidth() / 2,10 });
		}
	}
	glPopMatrix();
}

void InfoPlate::SetName(const std::string& name)
{
	delete m_pName;
	m_pName = new Texture{ name,"Resources/consola.ttf",16,Color4f{0,1,1,1} };
}
