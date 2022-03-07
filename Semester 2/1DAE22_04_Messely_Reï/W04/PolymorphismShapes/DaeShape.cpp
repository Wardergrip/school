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