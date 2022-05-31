#include "pch.h"
#include "Unit.h"
#include "utils.h"

#include <iostream>

// STATICS
bool Unit::c_IsDrawingHitboxes{ false };

void Unit::SetDrawingHitboxes(bool state)
{
	c_IsDrawingHitboxes = state;
}

void Unit::SwitchDrawingHitboxes()
{
	c_IsDrawingHitboxes = !c_IsDrawingHitboxes;
}

bool Unit::IsDrawingHitboxes()
{
	return c_IsDrawingHitboxes;
}

// NON STATICS
Unit::Unit(const Point2f& position, const Rectf& hitbox)
	:m_Hitbox{hitbox}
	,m_Transform{position}
	,m_Destination{position}
	,m_BasicStats{}
	,m_IsHoldingRightClick{false}
{
	CenterHitboxToPosition();
}

Unit::Unit(const Rectf& hitbox)
	:Unit({},hitbox)
{
	m_Transform.location = Point2f{ 0,0 };
}

bool Unit::IsOverlapping(const Point2f& point) const
{
	return utils::IsPointInRect(point,m_Hitbox);
}

bool Unit::IsOverlapping(const Rectf& rect) const
{
	return utils::IsOverlapping(m_Hitbox,rect);
}

bool Unit::IsOverlapping(const Circlef& circle) const
{
	return utils::IsOverlapping(m_Hitbox,circle);
}

bool Unit::IsOverlapping(const Unit& unit) const
{
	if (&unit == this) return true;
	return utils::IsOverlapping(this->m_Hitbox,unit.m_Hitbox);
}

void Unit::CenterTo(const Point2f& point)
{
	m_Transform.location = point;
	CenterHitboxToPosition();
}

void Unit::CenterHitboxToPosition()
{
	m_Hitbox.left = -m_Hitbox.width / 2;
	m_Hitbox.bottom = -m_Hitbox.height / 2;
}

const Transform& Unit::GetTransform() const
{
	return m_Transform;
}

void Unit::GetTransform(Transform& output) const
{
	output = m_Transform;
}

const BasicStats& Unit::GetBasicStats() const
{
	return m_BasicStats;
}

Rectf Unit::GetHitbox() const
{
	return m_Hitbox;
}

Rectf& Unit::GetHitbox(Rectf& output) const
{
	output = m_Hitbox;
	return output;
}

void Unit::DrawHitbox() const
{
	using namespace utils;
	SetColor(Color4f{ 1,0,0,1 });
	DrawRect(m_Hitbox, 2);
}

void Unit::MoveTowards(const Point2f& point)
{
	Vector2f direction{ point - m_Transform.location };
	if (direction.x < 1 && direction.x > -1)
	{
		if (direction.y < 1 && direction.y > -1)
		{

		}
		else
		{
			direction = direction.Normalized();
			m_Transform.location += (direction * m_BasicStats.movementSpeed);
		}
	}
	else
	{
		direction = direction.Normalized();
		m_Transform.location += (direction * m_BasicStats.movementSpeed);
	}
}

void Unit::OnMouseDownBasic(const SDL_MouseButtonEvent& e)
{
	switch (e.button)
	{
	case SDL_BUTTON_RIGHT:
		m_IsHoldingRightClick = true;
		m_Destination = Point2f{ float(e.x),float(e.y) };
		break;
	}
}

void Unit::OnMouseUpBasic(const SDL_MouseButtonEvent& e)
{
	switch (e.button)
	{
	case SDL_BUTTON_RIGHT:
		m_IsHoldingRightClick = false;
		break;
	}
}

void Unit::OnMouseMotionBasic(const SDL_MouseMotionEvent& e)
{
	if (m_IsHoldingRightClick)
	{
		m_Destination = Point2f{ float(e.x),float(e.y) };
	}
}

void Unit::Draw() const
{
	using namespace utils;
	// Drawing Destination
	/*SetColor(Color4f{ 0,1,0,1 });
	FillEllipse(m_Destination, 4, 4);*/

	m_Transform.Push();
	m_Transform.Apply();
	// Draw Unit
	SetColor(Color4f{1,1,1,1});
	FillEllipse(Point2f{ 0,0 }, 10, 10);
	
	// Draw hitbox
	if (c_IsDrawingHitboxes)
	{
		DrawHitbox();
	}
	m_Transform.Pop();
}

void Unit::Update(float elapsedSec)
{
	MoveTowards(m_Destination);
}

void Unit::OnMouseDown(const SDL_MouseButtonEvent& e)
{
	std::cout << "[UNIT] Default Mouse down\n";
}

void Unit::OnMouseUp(const SDL_MouseButtonEvent& e)
{
	std::cout << "[UNIT] Default Mouse up\n";
}

void Unit::OnMouseMotion(const SDL_MouseMotionEvent& e)
{
	std::cout << "[UNIT] Default Mouse motion\n";
}

void Unit::OnKeyDown(const SDL_KeyboardEvent& e, const Point2f& mousePos)
{
}

void Unit::OnKeyHold(float elapsedSec, const Uint8* pStates, const Point2f& mousePos)
{
}

void Unit::OnKeyUp(const SDL_KeyboardEvent& e, const Point2f& mousePos)
{
}
