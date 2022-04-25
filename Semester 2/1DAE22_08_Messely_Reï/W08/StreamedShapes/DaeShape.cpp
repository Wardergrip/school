#include "pch.h"
#include "DaeShape.h"

DaeShape::DaeShape(const Point2f& center, float width, float height, const Color4f& color)
	:m_Center{center}
	,m_Width{width}
	,m_Height{height}
	,m_Color{color}
{
}

DaeShape::~DaeShape()
{
}

void DaeShape::Translate(const Vector2f& tr)
{
	m_Center += tr;
}

std::string DaeShape::PropertiesToString() const
{
	std::string output;
	std::string helper{ '\"' };

	output += "Center=" + helper + std::to_string(m_Center.x) + ',' + std::to_string(m_Center.y) + helper + '\n';
	output += "Width=" + helper + std::to_string(m_Width) + helper + '\n';
	output += "Height=" + helper + std::to_string(m_Height) + helper + '\n';
	output += "Color=" + helper + std::to_string(m_Color.r) + ',' + std::to_string(m_Color.g) + ',' + std::to_string(m_Color.b) + ',' + std::to_string(m_Color.a) + helper + '\n';

	return output;
}
