#pragma once

#include "Transform.h"

class UserInterfaceElement
{
public:
	UserInterfaceElement(const Rectf& rect);
	UserInterfaceElement(const UserInterfaceElement& other) = delete;
	UserInterfaceElement& operator=(const UserInterfaceElement& other) = delete;
	UserInterfaceElement(UserInterfaceElement&& other) = delete;
	UserInterfaceElement& operator=(UserInterfaceElement&& other) = delete;
	virtual ~UserInterfaceElement();

	virtual void Draw() const;

	void SetRect(const Rectf& rect);
	void SetBL(const Point2f& bottomLeft);

	void CenterTo(const Point2f& center);

	Point2f GetCenter() const;
	bool IsInside(const Point2f& pos) const;

	void CenterRect(const Point2f& p = {});
	Point2f RectToBL() const;
	Point2f CenterOf() const;

private:
	Transform m_Transform;
	Rectf m_Rect;

	void UpdateTransform();
};
