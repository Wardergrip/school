#include "pch.h"
#include "UserInterfaceElement.h"

#include "utils.h"
using namespace utils;


UserInterfaceElement::UserInterfaceElement(const Rectf& rect)
	:m_Transform{}
	,m_Rect{rect}
{
	UpdateTransform();
}

UserInterfaceElement::~UserInterfaceElement()
{
}

void UserInterfaceElement::Draw() const
{
	m_Transform.Push();
	{
		m_Transform.Apply();
		FillRect(m_Rect);
	}
	m_Transform.Pop();
}

void UserInterfaceElement::SetRect(const Rectf& rect)
{
	m_Rect = rect;
	UpdateTransform();
}

void UserInterfaceElement::SetBL(const Point2f& bottomLeft)
{
	m_Rect.left = bottomLeft.x;
	m_Rect.bottom = bottomLeft.y;
	UpdateTransform();
}

void UserInterfaceElement::CenterTo(const Point2f& p)
{
	m_Rect = Rectf(p.x - (m_Rect.width / 2), p.y - (m_Rect.height / 2), m_Rect.width, m_Rect.height);
	UpdateTransform();
}

Point2f UserInterfaceElement::GetCenter() const
{
	return Point2f(m_Rect.left + m_Rect.width / 2, m_Rect.bottom + m_Rect.height / 2);
}

bool UserInterfaceElement::IsInside(const Point2f& pos) const
{
	return IsPointInRect(pos, m_Rect);
}

void UserInterfaceElement::CenterRect(const Point2f& p)
{
	m_Rect = Rectf(p.x - (m_Rect.width / 2), p.y - (m_Rect.height / 2), m_Rect.width, m_Rect.height);
	UpdateTransform();
}

Point2f UserInterfaceElement::RectToBL() const
{
	return Point2f(m_Rect.left + m_Rect.width / 16, m_Rect.bottom + m_Rect.height / 16);
}

Point2f UserInterfaceElement::CenterOf() const
{
	return Point2f(m_Rect.left + m_Rect.width / 2, m_Rect.bottom + m_Rect.height / 2);
}

void UserInterfaceElement::UpdateTransform()
{
	m_Transform.location = Point2f{ m_Rect.left,m_Rect.bottom };
}
