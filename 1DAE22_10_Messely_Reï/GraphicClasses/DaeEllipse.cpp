#include "pch.h"
#include "DaeEllipse.h"
#include <iostream>

DaeEllipse::DaeEllipse(const Point2f& center, float radX, float radY, const Color4f& fillColor)
	:m_Center{center}
	,m_RadX{radX}
	,m_RadY{radY}
	,m_FillColor{fillColor}
	,m_IsActive{false}
{
	m_Area = radX * radY * utils::g_Pi;
}

void DaeEllipse::Draw()
{
	if (m_IsActive)
	{
		utils::SetColor(m_FillColor);
	}
	else 
	{
		utils::SetColor(m_FillColor.r, m_FillColor.g, m_FillColor.b, m_FillColor.a / 2);
	}
	utils::FillEllipse(m_Center, m_RadX, m_RadY);
}

void DaeEllipse::ActivateTest(const Point2f& pos)
{
	// The ActivateTest method activates the ellipse when the parameter pos is within 
	// the ellipse boundaries(Point in an Ellipse).It deactivates the ellipse when this is
	// not the case.When a not- activated ellipse becomes activated, this method prints
	// its area to the console.
	const float calc{ (((pos.x - m_Center.x) * (pos.x - m_Center.x)) / (m_RadX * m_RadX)) + (((pos.y - m_Center.y) * (pos.y - m_Center.y)) / (m_RadY * m_RadY)) };
	if (calc <= 1)
	{
		if (!m_IsActive) std::cout << "Area of the ellipse is " << m_Area << '\n';
		m_IsActive = true;
	}
	else 
	{
		m_IsActive = false;
	}
}
