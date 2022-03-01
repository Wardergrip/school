#include "pch.h"
#include "ButtonBase.h"
#include "Texture.h"
#include "utils.h"
#include <iostream>
using namespace utils;

ButtonBase::ButtonBase(Texture* pTexture)
	:m_pTexture{pTexture}
	,m_Button{}
{
	if (m_pTexture != nullptr)
	{
		AdjustRectToTexture();
	}
}

ButtonBase::~ButtonBase()
{
	delete m_pTexture;
	m_pTexture = nullptr;
}

void ButtonBase::Draw() const
{
	DrawRect(m_Button);
	m_pTexture->Draw(m_Button);
}

void ButtonBase::SetRect(const Rectf& rect)
{
	m_Button = rect;
}

void ButtonBase::SetTexture(Texture* pTexture)
{
	m_pTexture = pTexture;
}

void ButtonBase::SetBL(const Point2f& bottomLeft)
{
	m_Button.left = bottomLeft.x;
	m_Button.bottom = bottomLeft.y;
}

void ButtonBase::CenterTo(const Point2f& p)
{
	m_Button = Rectf(p.x - (m_Button.width / 2), p.y - (m_Button.height / 2), m_Button.width, m_Button.height);
}

Point2f ButtonBase::GetCenter() const
{
	return Point2f(m_Button.left + m_Button.width / 2, m_Button.bottom + m_Button.height / 2);
}

bool ButtonBase::IsInside(const Point2f& pos) const
{
	return IsPointInRect(pos,m_Button);
}

void ButtonBase::CenterRect(const Point2f& p)
{
	m_Button = Rectf(p.x - (m_Button.width / 2), p.y - (m_Button.height / 2), m_Button.width, m_Button.height);
}

Point2f ButtonBase::RectToBL() const
{
	return Point2f(m_Button.left + m_Button.width / 16, m_Button.bottom + m_Button.height / 16);
}

Point2f ButtonBase::CenterOf() const
{
	return Point2f(m_Button.left + m_Button.width / 2, m_Button.bottom + m_Button.height / 2);
}

void ButtonBase::AdjustRectToTexture(float borderScale)
{
	m_Button = Rectf{
		m_Button.left - ((m_pTexture->GetWidth() * borderScale) / 2),
		m_Button.bottom - ((m_pTexture->GetHeight() * borderScale) / 2),
		(m_pTexture->GetWidth() * borderScale),(m_pTexture->GetHeight() * borderScale) };
}

// ---- STATICS ----

Point2f ButtonBase::Rect_to_BL(const Rectf& r)
{
	return Point2f(r.left + r.width / 16, r.bottom + r.height / 16);
}

Point2f ButtonBase::Center_of(const Rectf& r)
{
	return Point2f(r.left + r.width / 2, r.bottom + r.height / 2);
}

void ButtonBase::AdjustRect_to_Texture(Rectf& r, const Texture* t, float borderScale)
{
	r = Rectf{
		r.left - ((t->GetWidth() * borderScale) / 2),
		r.bottom - ((t->GetHeight() * borderScale) / 2),
		(t->GetWidth() * borderScale),(t->GetHeight() * borderScale) };
}

void ButtonBase::CenterRect(Rectf& r, const Point2f& p)
{
	r = Rectf(p.x - (r.width / 2), p.y - (r.height / 2), r.width, r.height);
}